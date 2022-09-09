#include <memory>
#include "models/car.h"
#include "helpers/scope.h"

int main()
{
    {
        Scope s("stack memory allocations");

        // Create object on stack
        Car car("porsche on stack");

        // Call method on stack object
        car.drive();
    }

    {
        Scope s("heap memory allocations");

        // Create object on stack
        Car *pCar = new Car("porsche on heap");

        // Call method on stack object
        pCar->drive();

        // If scope goes out without releasing pointer -> memory leak
        delete pCar;
    }

    {
        Scope s("unique_ptr - basics");

        // By default is initialized by nullptr
        std::unique_ptr<int> pNullptr;

        // Can be checked by "operator bool()"
        if(!pNullptr)
        {
            std::cout << "pNullptr is [nullptr]\n";
        }

        // Can be created from previously allocated space
        // indirectly, raw pointer should'n be used !!!
        auto *i = new int(123);
        std::unique_ptr<int> pInt1{i};

        // Value can be read by dereferencing
        std::cout << "pInt1:" << std::to_string(*pInt1) << "\n";

        // Can be created from previously allocated space
        // directly
        std::unique_ptr<int> pInt2{new int(456)};

        // Value can be changed
        *pInt2 = 555;
        std::cout << "pInt2:" << std::to_string(*pInt2) << "\n";

        // Non trivial typed can be used
        std::unique_ptr<Car> pPorsche{new Car("porsche 1")};

        // Methods of non-trivial objects can be called
        pPorsche->drive();

        // Object can be constructed without 'new' operator
        // arguments can be passed to 'make_unique'
        auto pBwm = std::make_unique<Car>("BWM");

        // Value can be retrived by 'get' method
        pBwm.get()->drive();

        // Cannot be copied by copy constructor
        // "error: use of deleted function std::unique_ptr<...>(...)"
        //auto pBwmCopy{pBwm};

        // Cannot be copied by copy operator
        // "error: use of deleted function std::unique_ptr<...>::operator=(...)"
        //std::unique_ptr<Car> pBwmCopy;
        //pBwmCopy = pBwm;
    }

    {
        Scope s("unique_ptr - transfer ownership");

        std::unique_ptr<Car> pCar1 = std::make_unique<Car>("car1");

        // Transfer ownership by 'std::move'
        auto pCar2 = std::move(pCar1);

        if(!pCar1)
        {
            std:: cout << "pCar1 becomes nullptr\n";
        }

        if(pCar2)
        {
            std:: cout << "pCar2 takes ownership of pCar1 object\n";
            pCar2->drive();
        }
    }

    {
        Scope s("unique_ptr - pass by value");

        // pass pointer by value
        // ownership is transferred to function
        auto jobByLValue = [](std::unique_ptr<Car> pCar){
            Scope s("jobByValue");
            pCar->drive();
            std::cout << "'pCar' will be deleted here\n";
            // here destructor of 'pCar' is called
        };

        auto pCar1 = std::make_unique<Car>("car1");

        // cannot share ownership
        // compilation error
        //jobByLValue(pCar1);

        // l-value object ownership is transferred to function
        jobByLValue(std::move(pCar1));

        // r-value object can be transferred implicitly
        jobByLValue(std::make_unique<Car>("car1"));
    }

    {
        Scope s("unique_ptr - pass by reference");

        // pass pointer by reference
        // ownership is not transferred
        // only wrapped object can be modified
        auto jobByConstReference = [](const std::unique_ptr<Car> &pCar){
            Scope s("jobByConstReference");

            // object can be modified - non const method called
            pCar->drive();

            // non-const method of pointer wrapper class cannot be called
            //pCar.reset();
        };

        auto pCar1 = std::make_unique<Car>("car1");

        // lk-value object can be passed
        // ownership is not transferred
        jobByConstReference(pCar1);
    }

    {
        Scope s("unique_ptr - return from function");

        auto buildObject = [](){
            auto pCar = std::make_unique<Car>("local car");
            pCar->print_address();

            // compiler makes optimizations
            // copy is not returned
            // returned value is reference to local object
            // behaviour depends on used compiler
            return pCar;
        };

        auto pCar = buildObject();
        pCar->print_address();
    }

}
