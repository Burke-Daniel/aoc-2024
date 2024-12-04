#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(void) {
    std::ifstream input("day2_input.txt");

    std::vector<std::vector<size_t>> reports;

    // Make reports

    for (std::string line; std::getline(input, line);) {
        std::vector<size_t> report;

        std::cout << "New report:\n";

        std::istringstream iss(line);
        std::string level;

        while (std::getline(iss, level, ' ')) {
            std::cout << "Putting " << level << " in report\n";
            report.push_back(std::stoul(level));
        }

        reports.push_back(report);
    }

    // Check reports

    std::cout << "Part one:\n";
    
    size_t num_safe = 0;
    
    for (const std::vector<size_t>& report : reports) {
        // Assuming that a report is at least 2 elements long
        
        bool increasing = report[1] > report[0];
        size_t previous = report[0];

        bool safe = true;
        for (size_t i = 1; i < report.size(); i++) {
            if (increasing && report[i] < previous ||
                !increasing && report[i] > previous) {
                safe = false;
                break;
            }

            if (previous == report[i] || abs(report[i] - previous) > 3) {
                safe = false;
                break;
            }

            previous = report[i];
        }

        if (safe) num_safe++;
        else printf("Report is not safe!\n");
    }

    std::cout << "Num safe: " << num_safe << '\n';

    // Part 2

    std::cout << "Part Two:\n";

    num_safe = 0;

    for (std::vector<size_t>& report : reports) {
        // Assuming that a report is at least 2 elements long
        
        std::vector<std::vector<size_t>> possible_reports = {
            report,
        };

        // Generate all the other possible reports
        // with one element removed
        for (size_t i = 0; i < report.size(); i++) {
            std::vector<size_t> report_copy;

            for (size_t j = 0; j < report.size(); j++) {
                if (j == i) continue;

                report_copy.push_back(report[j]);
            }

            possible_reports.push_back(report_copy);
        }

        printf("\nBegin checking all possible reports\n");

        for (auto possible_report : possible_reports) {
            printf("Checking Report: ");
            for (size_t level : possible_report) {
                printf("%lu ", level);
            }
            printf("\n");

            
            bool increasing = possible_report[1] > possible_report[0];
            size_t previous = possible_report[0];

            bool safe = true;
            for (size_t i = 1; i < possible_report.size(); i++) {
                if (increasing && possible_report[i] < previous) {
                    safe = false;
                    printf("Element %d is less than previous element %d\n", possible_report[i], previous);
                    break;
                } else if (!increasing && possible_report[i] > previous) {
                    safe = false;
                    printf("Element %d is greater than previous element %d\n", possible_report[i], previous);
                    break;
                }

                if (previous == possible_report[i] || abs(possible_report[i] - previous) > 3) {
                    safe = false;
                    printf("Element %d is equal to or greater than 3 in difference to %d\n", possible_report[i], previous);
                    break;
                }

                previous = possible_report[i];
            }

            if (safe)
            {
                printf("Safe!\n");
                num_safe++;
                break;
            }
        }

        printf("End checking all possible reports\n");
    }

    std::cout << "Num safe: " << num_safe << '\n';

    return 0;
}
