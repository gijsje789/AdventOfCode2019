#include <iostream>
#include <string>

static int range_l = 256310;
static int range_u = 732736;

int main()
{
    char prev_char;
    bool adjacent_OK = false;
    bool noDecrease_OK = true;
    int possibilities = 0;
    int prev_cntr = 0;
    for(int i = range_l; i <= range_u; i++) {
        std::string password = std::to_string(i);
        prev_char = password[0];
        adjacent_OK = false;
        noDecrease_OK = true;
        prev_cntr = 0;
        for(size_t j = 1; j < password.size(); j++) {
            if(password[j] == prev_char) {
                prev_cntr++;
            } else {
                if(prev_cntr == 1) adjacent_OK = true;
                prev_cntr = 0;
            }
            if((password[j]-'0') < (prev_char-'0')) noDecrease_OK = false;
            prev_char = password[j];
        }
        if(prev_cntr == 1) adjacent_OK = true;
        if(adjacent_OK && noDecrease_OK) possibilities++;
   }
    std::cout << "Possibilities: " << possibilities << std::endl;
    return 0;
}
