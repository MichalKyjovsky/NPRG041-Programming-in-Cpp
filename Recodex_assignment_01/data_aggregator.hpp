//
// Created by mkyjovsky01 on 12/12/2020.
//

#ifndef RECODEX_ASSIGNMENT_01_DATA_AGGREGATOR_HPP
#define RECODEX_ASSIGNMENT_01_DATA_AGGREGATOR_HPP

#include <iostream>
#include <utility>
#include <variant>
#include <string>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <map>
#include <algorithm>
#include <cctype>
#include <queue>


class DataAggregator {
private:


    enum ExtremeFunctionAggregation {
        MINIMUM = 0,
        MAXIMUM = 1
    };

    enum AggregationMethod {
        SUM = 0,
        MIN = 1,
        MAX = 2,
        NONE = 3
    };

    typedef struct {
        // Aggregation key will be only one
        std::string aggregation_attribute;
        /**
         * Following data structure assumes format where the dictionary key will be
         * the attribute (column name) and its value enumeration of the aggregation
         * method used over this column. Since each aggregation method may be applied
         * on each column just once, the REPEATING CALLS OF THE AGGREGATION SAME METHOD
         * WILL BE OMITTED
         * */
        std::vector<std::pair<std::string, AggregationMethod>> aggregation_tuples;
    } decomposed_query_t;

    typedef std::variant<std::string, int, double> attribute_t;

    typedef std::vector<attribute_t> record_t;
    typedef std::vector<record_t> data_table_t;
    typedef std::vector<std::string> header_t;
    typedef std::vector<std::string> type_specification_t;
    typedef std::vector<std::vector<std::string>> raw_data_t;

    std::string raw_query;

    std::size_t records_number;
    std::size_t attributes_number;
    std::size_t aggregator_index;
    header_t table_header;
    type_specification_t type_specification;
    data_table_t table_data;
    decomposed_query_t decomposed_query;

    void update_aggregation_method_for_column(const std::string &raw_column_name, AggregationMethod aggregationMethod,
                                              bool trunc = true);

    void parse_raw_query(std::istream &raw_query_stream) {
        std::string query;
        raw_query_stream.ignore();
        std::getline(raw_query_stream, query);
        parse_raw_query(query);
    }

    void parse_raw_query(const std::string &raw_query);

    static header_t parse_table_header(const std::string& raw_header, char delimiter = ';');

    static header_t parse_table_header(std::istream &raw_header_stream) {
        std::string input_header_buffer;
        raw_header_stream >> input_header_buffer;
        return parse_table_header(input_header_buffer);
    }

    static std::vector<std::string> aggregator_parse_joined_line(const std::string& raw_line, char delimiter = ';');


    static type_specification_t
    parse_type_specification(const std::string &raw_type_specification, char delimiter = ';');

    static type_specification_t
    parse_type_specification(std::istream &raw_type_specification_stream, char delimiter = ';') {
        std::string raw_type_specification;
        raw_type_specification_stream >> raw_type_specification;
        return parse_type_specification(raw_type_specification, delimiter);
    }

    record_t parse_raw_record(std::istream &raw_data_stream, char delimiter = ';') {
        std::string temp_record_string;
        raw_data_stream >> temp_record_string;
        return parse_raw_record(temp_record_string, delimiter);
    }

    record_t parse_raw_record(const std::string &raw_record, char delimiter = ';');


    static std::size_t parse_raw_records_number(std::istream &raw_records_number_stream) {
        std::string records_number_temp;
        raw_records_number_stream >> records_number_temp;
        return std::stoi(records_number_temp);
    }

    //TODO: It is not intended to fill data via constructor as for now
    static data_table_t parse_raw_data(const raw_data_t &raw_data) {
        /**
         * As for now there is no need for implementation
         * */

        data_table_t t;
        return t;
    }


    static attribute_t aggregator_perform_sum_operation(size_t column_index, const data_table_t &data);

    static attribute_t aggregator_perform_extreme_operation(size_t column_index, const data_table_t &data,
                                                            ExtremeFunctionAggregation func);

    void aggregator_load_header() {
        this->table_header = parse_table_header(std::cin);
    }

    void aggregator_load_data_types() {
        this->type_specification = parse_type_specification(std::cin);
    }

    void aggregator_load_number_of_records() {
        this->records_number = parse_raw_records_number(std::cin);
    }

    void aggregator_load_records();

    void aggregator_load_query() {
        //TODO: Implement query structure in order to hold parameters to data querying
        parse_raw_query(std::cin);

    }

    void aggregator_load_attributes_number() {
        this->attributes_number = this->table_header.size();
    }

    std::queue<attribute_t> create_aggregators();

    std::size_t get_column_index(const std::string &column_name);

    void print_query_results(const data_table_t &data) const;

    void print_queried_header() const;

public:
    DataAggregator() = default;

    DataAggregator(const std::string &header, const std::string &type_specification, std::size_t records_number,
                   const raw_data_t &data,
                   std::string query) : table_header{DataAggregator::parse_table_header(header)},
                                        type_specification{
                                                DataAggregator::parse_type_specification(type_specification)},
                                        records_number{records_number},
                                        table_data{DataAggregator::parse_raw_data(data)},
                                        raw_query{std::move(query)} {
        /**
         * Initialization done by ctor member initialization.
         * No need to do anything else, data load will be covered elsewhere.
         * TODO: Specify where.
         * */
    }

    DataAggregator(const DataAggregator &dataAggregator) : table_header{dataAggregator.table_header},
                                                           type_specification{dataAggregator.type_specification},
                                                           records_number{dataAggregator.records_number},
                                                           table_data{dataAggregator.table_data},
                                                           raw_query{dataAggregator.raw_query} {
        /**
         * Copy ctor.
         * No other operation is required.
         * */
    }

    DataAggregator(DataAggregator &&dataAggregator) : table_header{std::move(dataAggregator.table_header)},
                                                      type_specification{std::move(dataAggregator.type_specification)},
                                                      records_number{dataAggregator.records_number},
                                                      table_data{std::move(dataAggregator.table_data)},
                                                      raw_query{std::move(dataAggregator.raw_query)} {
        /**
         * Move ctor.
         * No other operation is required.
         * */
    }

    // No dynamic allocation, default should do fine
    ~DataAggregator() = default;

    DataAggregator &operator=(const DataAggregator &dataAggregator) {
        this->table_header = dataAggregator.table_header;
        this->type_specification = dataAggregator.type_specification;
        this->records_number = dataAggregator.records_number;
        this->table_data = dataAggregator.table_data;
        this->raw_query = dataAggregator.raw_query;
        return *this;
    }

    DataAggregator &operator=(DataAggregator &&dataAggregator) {
        this->table_header = std::move(dataAggregator.table_header);
        this->type_specification = std::move(dataAggregator.type_specification);
        this->records_number = dataAggregator.records_number;
        this->table_data = std::move(dataAggregator.table_data);
        this->raw_query = std::move(dataAggregator.raw_query);
        return *this;
    }

    void aggregator_load_data();

    void evaluate_query_over_dataset();

};


#endif //RECODEX_ASSIGNMENT_01_DATA_AGGREGATOR_HPP
