//
// Created by mkyjovsky01 on 12/12/2020.
//

#include "data_aggregator.hpp"
#include <sstream>

void DataAggregator::aggregator_load_data() {
    this->aggregator_load_header();
    this->aggregator_load_data_types();
    this->aggregator_load_attributes_number();
    this->aggregator_load_number_of_records();
    this->aggregator_load_records();
    this->aggregator_load_query();
}

DataAggregator::header_t DataAggregator::parse_table_header(const std::string& raw_header, char delimiter) {
    return aggregator_parse_joined_line(raw_header, delimiter);
}


DataAggregator::type_specification_t
DataAggregator::parse_type_specification(const std::string &raw_type_specification, char delimiter) {
    return aggregator_parse_joined_line(raw_type_specification, delimiter);
}


void DataAggregator::aggregator_load_records() {
    for (int i = 0; i < this->records_number; ++i) {
        this->table_data.push_back(this->parse_raw_record(std::cin));
    }
}

std::vector<std::string> DataAggregator::aggregator_parse_joined_line(const std::string& raw_line, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;

    std::istringstream token_stream(raw_line);

    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(std::move(token));
    }
    return tokens;
}

DataAggregator::record_t DataAggregator::parse_raw_record(const std::string &raw_record, char delimiter) {

    std::vector<std::string> split_data = aggregator_parse_joined_line(raw_record, delimiter);

    record_t temp_record;

    assert(attributes_number == split_data.size() &&
           "The number of attributes in the given record exceeds the defined number of attributes in the table.");

    for (int i = 0; i < this->attributes_number; ++i) {
        //TODO: Switch for some sort of enum, this String comparison is ugly
        if (this->type_specification[i] == "string") {
            temp_record.push_back(split_data[i]);
        } else if (this->type_specification[i] == "int") {
            temp_record.push_back(std::stoi(split_data[i]));
        } else if (this->type_specification[i] == "double") {
            temp_record.push_back(std::stod(split_data[i]));
        } else {
            throw std::invalid_argument("Illegal argument exception!");
        }
    }
    return temp_record;
}


//TODO: Add ' ' delimiter to constant
void DataAggregator::parse_raw_query(const std::string &query) {
    // Split query by white spaces
    std::vector<std::string> raw_query_split = aggregator_parse_joined_line(query, ' ');

    this->decomposed_query.aggregation_attribute = raw_query_split[raw_query_split.size() - 1];
    // Start from the index 1, since the SELECT itself is not interesting at all.
    for (auto col : raw_query_split) {
        // Make all OPS lower case
        std::transform(col.begin(), col.end(), col.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (col.rfind("sum", 0) == 0) {
            this->update_aggregation_method_for_column(col, AggregationMethod::SUM);
        } else if (col.rfind("min", 0) == 0) {
            this->update_aggregation_method_for_column(col, AggregationMethod::MIN);
        } else if (col.rfind("max", 0) == 0) {
            this->update_aggregation_method_for_column(col, AggregationMethod::MAX);
        } else if (col == "group_by") {
            break;
        } else if (col == "select") {
            continue;
        } else {
            this->update_aggregation_method_for_column(col, AggregationMethod::NONE, false);
        }
    }
}

void DataAggregator::update_aggregation_method_for_column(const std::string &raw_column_name,
                                                          DataAggregator::AggregationMethod aggregationMethod,
                                                          bool trunc) {

    std::string column_name;

    if (trunc) {
        std::size_t column_name_length = raw_column_name.find(')');
        column_name = raw_column_name.substr(4, column_name_length - 4);
    } else {
        std::size_t column_name_length = raw_column_name.find(',');
        column_name = column_name_length != std::string::npos ? raw_column_name.substr(0, column_name_length)
                                                              : raw_column_name.substr(0, raw_column_name.size() - 1);
    }

    std::pair<std::string, AggregationMethod> aggregation_query_item = std::make_pair(column_name, aggregationMethod);

    if (std::find(this->decomposed_query.aggregation_tuples.begin(), this->decomposed_query.aggregation_tuples.end(),
                  aggregation_query_item) == this->decomposed_query.aggregation_tuples.end()) {
        this->decomposed_query.aggregation_tuples.push_back(aggregation_query_item);
    } else {
        // The aggregation over the column was already performed -> DO NOTHING
    }

}

void DataAggregator::evaluate_query_over_dataset() {
    // Values of attribute of records, base on which the aggregation will be performed
    std::queue<attribute_t> aggregation_keys = this->create_aggregators();

    data_table_t intermediate_out_struct;

    record_t temporary_record;

    data_table_t output_table;

    while (!aggregation_keys.empty()) {
        attribute_t current_aggregator = aggregation_keys.front();

        for (auto record : this->table_data) {
            // copy allowed
            if (record.at(this->aggregator_index) == current_aggregator) {
                /**
                 * Iterate over columns from left to right and perform aggregation issued over this columns
                 * */
                intermediate_out_struct.push_back(record);
            }
        }

        for (auto const &aggr : this->decomposed_query.aggregation_tuples) {
            size_t current_aggregated_col_idx = this->get_column_index(aggr.first);

            switch (aggr.second) {
                case SUM: {
                    temporary_record.push_back(aggregator_perform_sum_operation(current_aggregated_col_idx,
                                                                                intermediate_out_struct));
                    break;
                }
                case MIN: {
                    temporary_record.push_back(aggregator_perform_extreme_operation(current_aggregated_col_idx,
                                                                                    intermediate_out_struct, MINIMUM));
                    break;
                }
                case MAX: {
                    temporary_record.push_back(aggregator_perform_extreme_operation(current_aggregated_col_idx,
                                                                                    intermediate_out_struct, MAXIMUM));
                    break;
                }
                case NONE:
                    // Push the name of the aggregator, if required in the output
                    temporary_record.push_back(intermediate_out_struct.at(0).at(current_aggregated_col_idx));
            }

        }

        output_table.push_back(temporary_record);
        temporary_record.clear();
        intermediate_out_struct.clear();
        aggregation_keys.pop();
    }
    print_query_results(output_table);

}

std::queue<DataAggregator::attribute_t> DataAggregator::create_aggregators() {

    this->aggregator_index = this->get_column_index(this->decomposed_query.aggregation_attribute);

    assert(aggregator_index != -1 && "Column set for aggregation does not exists.");

    record_t aggregation_keys;

    for (const auto &record : this->table_data) {
        if (std::find(aggregation_keys.begin(), aggregation_keys.end(), record.at(this->aggregator_index)) ==
            aggregation_keys.end()) {
            /* aggregation_keys does not contains the aggregator value yet */
            aggregation_keys.push_back(record.at(this->aggregator_index));
        }
    }

    std::queue<attribute_t> aggregation_keys_queue;

    for (const auto &key : aggregation_keys) {
        aggregation_keys_queue.push(key);
    }

    return aggregation_keys_queue;
}

//TODO: Consider to remake into service, i.e static method
std::size_t DataAggregator::get_column_index(const std::string &column_name) {
    std::size_t index_counter = 0;
    for (const auto &item : this->table_header) {
        if (column_name == item) {
            return index_counter;
        }
        ++index_counter;
    }
    return -1;
}

DataAggregator::attribute_t
DataAggregator::aggregator_perform_sum_operation(size_t column_index, const data_table_t &data) {
    attribute_t out_attr;
    //TODO: Design workaround, this is ugly
    std::string out_attr_str;
    int out_attr_int = 0;
    double out_attr_double = 0;

    // TODO: Substitute for ENUM
    switch (data.at(0).at(column_index).index()) {
        case 0:
            for (const auto &record : data) {
                out_attr_str += std::get<std::string>(record.at(column_index));
            }
            out_attr = out_attr_str;
            break;
        case 1:
            for (const auto &record : data) {
                out_attr_int += std::get<int>(record.at(column_index));
            }
            out_attr = out_attr_int;
            break;
        case 2:
            for (const auto &record : data) {
                out_attr_double += std::get<double>(record.at(column_index));
            }
            out_attr = out_attr_double;
            break;
    }

    return out_attr;
}

DataAggregator::attribute_t
DataAggregator::aggregator_perform_extreme_operation(size_t column_index, const data_table_t &data,
                                                     ExtremeFunctionAggregation func) {
    switch (data.at(0).at(column_index).index()) {
        case 0: {
            std::vector<std::string> out_buff;
            for (const auto &record : data) {
                out_buff.push_back(std::get<std::string>(record.at(column_index)));
            }
            return func == MINIMUM ? out_buff.at(
                    std::distance(out_buff.begin(), std::min_element(out_buff.begin(), out_buff.end()))) : out_buff.at(
                    std::distance(out_buff.begin(), std::max_element(out_buff.begin(), out_buff.end())));
        }
        case 1: {
            std::vector<int> out_buff;
            for (const auto &record : data) {
                out_buff.push_back(std::get<int>(record.at(column_index)));
            }
            return func == MINIMUM ? out_buff.at(
                    std::distance(out_buff.begin(), std::min_element(out_buff.begin(), out_buff.end()))) : out_buff.at(
                    std::distance(out_buff.begin(), std::max_element(out_buff.begin(), out_buff.end())));
        }
        case 2: {
            std::vector<double> out_buff;
            for (const auto &record : data) {
                out_buff.push_back(std::get<double>(record.at(column_index)));
            }
            return func == MINIMUM ? out_buff.at(
                    std::distance(out_buff.begin(), std::min_element(out_buff.begin(), out_buff.end()))) : out_buff.at(
                    std::distance(out_buff.begin(), std::max_element(out_buff.begin(), out_buff.end())));
        }
        default:
            return 0;
    }
}

void DataAggregator::print_query_results(const DataAggregator::data_table_t &data) const {

    this->print_queried_header();

    size_t semicolon_count = this->decomposed_query.aggregation_tuples.size();
    size_t counter = 0;

    for (const auto &record : data) {
        for (const auto &attr : record) {
            switch (attr.index()) {
                case 0:
                    std::cout << std::get<std::string>(attr);
                    break;
                case 1:
                    std::cout << std::get<int>(attr);
                    break;
                case 2:
                    std::cout << std::fixed << std::get<double>(attr);
                    break;
            }
            if (counter < semicolon_count - 1) {
                std::cout << ";";
                ++counter;
            }
        }
        counter = 0;
        std::cout << std::endl;
    }
}

void DataAggregator::print_queried_header() const {
    size_t semicolon_count = this->decomposed_query.aggregation_tuples.size();
    size_t counter = 0;

    for (const auto &col : this->decomposed_query.aggregation_tuples) {
        switch (col.second) {
            case SUM:
                std::cout << "SUM(" << col.first << ")";
                break;
            case MIN:
                std::cout << "MIN(" << col.first << ")";
                break;
            case MAX:
                std::cout << "MAX(" << col.first << ")";
                break;
            case NONE:
                std::cout << col.first;
                break;
        }
        if (counter < semicolon_count - 1) {
            std::cout << ";";
            ++counter;
        }
    }
    std::cout << std::endl;
}
