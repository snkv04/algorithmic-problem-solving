#include <bits/stdc++.h>
using namespace std;

// return_type function_name(datatype1 variable1, datatype2 variable2) {
//     function_body (which is all the code inside the function)
// }
int combine(int x, int y) {
    int first_term = 2 * x;
    int second_term = 3 * y;
    return first_term + second_term;
}

int main() {
    // Input/output
    {
        // Tells computer to print something
        std::cout << "Hello, what is your name? ";

        // This line pulls in the input
        std::string name;
        std::cin >> name;

        // This line pushes out new output
        std::cout << "Your name is: " << name << std::endl;
    }

    // Datatypes
    {
        // Integers

        // Creates a variable named x
        // x must hold a value that is an integer
        // Gives x the value of 5 (so now x holds the value 5)
        int x = 5;
        x = x + 7;
        x = 9;

        // Floats
        float y = 1.7;
        y = 1.0;
        float z = x + y;
        std::cout << "z = " << z << std::endl;

        // Strings
        string name = "neelu";

        // Booleans
        bool payment_made = true;
        payment_made = false;

        // Arrays/vectors
        vector<int> heights = {67, 61, 70, 67};
        cout << heights[1] << endl;
    }

    // If conditions
    {
        std::string pencil_color = "blue";
        if (pencil_color == "yellow") {
            std::cout << "This pencil is normal!" << std::endl;
            // possibly hundreds of other lines of code
        } else {
            std::cout << "This is a weird pencil!" << std::endl;
        }

        // some other code
    }

    // For loops
    {
        /*
        final sum=0

        take the first number. If it's odd skip to next number.
        Now the number is 2 and even, so it will add to final sum.
        Move to 3, skip
        Move to 4, add with final sum
        ...
        move to 16, add with final sum
        */
        
        int final_sum = 0;
        for (int current_number = 1; current_number <= 16; current_number = current_number + 1) {
            // std::cout << "current_number is equal to " << current_number << std::endl;
            if (current_number % 2 == 0) {
                // std::cout << "that number is even, so we will add" << std::endl;
                final_sum = final_sum + current_number;
                // std::cout << "after adding, final_sum is now equal to " << final_sum << std::endl;
            } else {
                // std::cout << "that number is odd, so we will skip" << std::endl;
            }
            // std::cout << std::endl;
        }
        std::cout << "at the end, final_sum is equal to " << final_sum << std::endl;
        
        int final_product = 1;
        std::vector<int> heights = {67, 61, 70, 67};
        for (int current_index = 0; current_index <= 3; current_index = current_index + 1) {
            final_product = final_product * heights[current_index];
        }
        std::cout << "at the end, final_product = " << final_product << std::endl;
    }

    // Functions
    {
        int x = 2;
        int y = 4;
        int z = combine(x, y);
        cout << "z = " << z << endl;
    }

    return 0;
}
