#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <nanobench.h>
#include "Sort.h"

int MAX_LENGTH = 100;
int REPETITION_COUNT = 5000;

int main() {

    /*
    std::ofstream file("THRESHOLD.csv", std::ofstream::out | std::ofstream::trunc);
    file << "count;insertion_avg_ns;quick_avg_ns\n";

    for (int size = 1; size <= MAX_LENGTH; size++)
    {
        std::vector<int> original_data(size);
        for (int i = 0; i < size; i++)
        {
            original_data[i] = size - i;
        }

        double insertion_total_time = 0.0;
        double quick_total_time = 0.0;

        for (int rep = 0; rep < REPETITION_COUNT; rep++)
        {
            std::vector<int> data_for_insertion = original_data;
            ankerl::nanobench::Bench bench_insertion;
            bench_insertion.epochs(1).epochIterations(1).output(nullptr);

            bench_insertion.run("Insertion Sort", [&]()
            {
                insertionSort(data_for_insertion.data(), data_for_insertion.data() + size, compare);
            });

            auto const& result_insertion = bench_insertion.results();
            if (!result_insertion.empty())
            {
                std::ostringstream oss;
                bench_insertion.render(ankerl::nanobench::templates::csv(), oss);
                std::string csv_output = oss.str();

                std::istringstream iss(csv_output);
                std::string line;
                std::getline(iss, line); // header
                std::getline(iss, line); // data
                if (!line.empty())
                {
                    std::istringstream data_iss(line);
                    std::string field;
                    int col_idx = 0;
                    double elapsed_s = 0.0;
                    while (std::getline(data_iss, field, ';'))
                    {
                        if (col_idx == 4)
                        {
                            if (field.front() == '"' && field.back() == '"')
                            {
                                field = field.substr(1, field.length() - 2);
                            }
                            elapsed_s = std::stod(field);
                            break;
                        }
                        col_idx++;
                    }
                    insertion_total_time += elapsed_s * 1e9;
                }
            }

            std::vector<int> data_for_quick = original_data;
            ankerl::nanobench::Bench bench_quick;
            bench_quick.epochs(1).epochIterations(1).output(nullptr);

            bench_quick.run("Quick Sort", [&]()
            {
                quickSort(data_for_quick.data(), data_for_quick.data() + size, compare);
            });

            auto const& result_quick = bench_quick.results();
            if (!result_quick.empty())
            {
                std::ostringstream oss;
                bench_quick.render(ankerl::nanobench::templates::csv(), oss);
                std::string csv_output = oss.str();

                std::istringstream iss(csv_output);
                std::string line;
                std::getline(iss, line);
                std::getline(iss, line);
                if (!line.empty())
                {
                    std::istringstream data_iss(line);
                    std::string field;
                    int col_idx = 0;
                    double elapsed_s = 0.0;
                    while (std::getline(data_iss, field, ';'))
                    {
                        if (col_idx == 4)
                        {
                            if (field.front() == '"' && field.back() == '"')
                            {
                                field = field.substr(1, field.length() - 2);
                            }
                            elapsed_s = std::stod(field);
                            break;
                        }
                        col_idx++;
                    }
                    quick_total_time += elapsed_s * 1e9;
                }
            }
        }

        double insertion_avg_ns = insertion_total_time / static_cast<double>(REPETITION_COUNT);
        double quick_avg_ns = quick_total_time / static_cast<double>(REPETITION_COUNT);

        file << size << ";" << insertion_avg_ns << ";" << quick_avg_ns << "\n";
    }

    file.close();
    */

    std::string command = "python C:\\Users\\User\\CLionProjects\\Lab3\\plot.py THRESHOLD.csv";
    int result = std::system(command.c_str());

    return 0;
}