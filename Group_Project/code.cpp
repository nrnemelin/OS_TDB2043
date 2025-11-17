#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::sort and std::transform
#include <cmath>     // For std::abs
#include <iomanip>   // For std::setw (formatting output)
#include <sstream>   // For std::stringstream (to read the list)
#include <limits>    // For std::numeric_limits (to clear input buffer)

void c_scan(std::vector<int> requests, int head, std::string direction, int disk_max) {
    int disk_min = 0;
    int total_travel = 0;
    std::vector<int> service_sequence;

    service_sequence.push_back(head);

    // 1. Sort the requests
    std::sort(requests.begin(), requests.end());

    if (direction == "UP") {
        // Direction: UP
        for (int i = 0; i < requests.size(); ++i) {
            if (requests[i] >= head) {
                service_sequence.push_back(requests[i]);
            }
        }
        service_sequence.push_back(disk_max);
        service_sequence.push_back(disk_min);
        for (int i = 0; i < requests.size(); ++i) {
            if (requests[i] < head) {
                service_sequence.push_back(requests[i]);
            } else {
                break;
            }
        }
    } 
    else if (direction == "DOWN") {
        // Direction: DOWN
        for (int i = requests.size() - 1; i >= 0; --i) {
            if (requests[i] <= head) {
                service_sequence.push_back(requests[i]);
            }
        }
        service_sequence.push_back(disk_min);
        service_sequence.push_back(disk_max);
        for (int i = requests.size() - 1; i >= 0; --i) {
            if (requests[i] > head) {
                service_sequence.push_back(requests[i]);
            } else {
                break;
            }
        }
    }

    // Print the results
    std::cout << "\nC-SCAN Results" << std::endl;
    std::cout << "Initial Arm Position: " << head << "\t";
    std::cout << "Direction: " << direction << "\n\n";
    
    std::cout << std::left << std::setw(10) << "Start"
              << std::setw(10) << "Finished"
              << std::setw(10) << "Track Travelled" << "\n";
    std::cout << "--------------------------------\n";

    for (size_t i = 0; i < service_sequence.size() - 1; ++i) {
        int start = service_sequence[i];
        int end = service_sequence[i+1];
        int travel = std::abs(end - start);
        
        total_travel += travel;

        std::cout << std::left << std::setw(10) << start
                  << std::setw(10) << end
                  << std::setw(10) << travel << "\n";
    }

    std::cout << "\nTotal Track Travelled: " << total_travel << "\n";
}

/* Main function to get user input and run the simulation.
 * (This function is NEW and handles user input)
 */
int main() {
    // Variables to store user input
    int initial_head;
    std::string direction;
    std::vector<int> requests;
    std::string request_line;

    // Disk size is fixed from 0 to 199
    int disk_size_max = 199;

    // 1. Get Initial Head Position
    std::cout << "Enter the initial arm position (e.g., 50): ";
    std::cin >> initial_head;

    // 2. Get Direction
    while (true) {
        std::cout << "Enter the direction (UP or DOWN): ";
        std::cin >> direction;
        
        // Convert input to uppercase to be flexible (handles "up" or "down")
        std::transform(direction.begin(), direction.end(), direction.begin(), ::toupper);
        
        if (direction == "UP" || direction == "DOWN") {
            break; // Valid input, exit loop
        } else {
            std::cout << "Invalid input. Please enter UP or DOWN.\n";
        }
    }

    // 3. Get List of Track Requests
    std::cout << "Enter the list of track requests (e.g., 85 10 37 175): ";
    
    // Clear the input buffer
    // This is necessary because std::cin (from reading 'direction')
    // leaves a newline character ('\n') that std::getline would read.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    
    // Read the entire line of space-separated numbers
    std::getline(std::cin, request_line);
    
    // Use a stringstream to "parse" the numbers from the line
    std::stringstream ss(request_line);
    int req_num;
    
    // Read each number from the stringstream and add it to the vector
    while (ss >> req_num) {
        requests.push_back(req_num);
    }

    // Run the simulation
    c_scan(requests, initial_head, direction, disk_size_max);

    return 0;
}
