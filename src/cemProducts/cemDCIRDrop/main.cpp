# include <iostream>

int main(int argc,char *argv[])
{
    if (argc < 3)
        std::cout << "You must enter the month and year!" << std::endl;
    else
    {
        std::cout << "Month is: " << argv[1] << std::endl;
        std::cout << "Year is: " << argv[2] << std::endl;
    }
}
