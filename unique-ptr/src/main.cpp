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
        Scope s("unique_ptr overview");

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
        Scope s("unique_ptr transfer ownership");

        std::unique_ptr<Car> pCar1 = std::make_unique<Car>("car1");

        // Transfer ownership by 'std::move'
        auto pCar2 = std::move(pCar1);

        // 2. unique_ptr can be created from previously allocated space
        // directly
        std::unique_ptr<Car> pCarDirect{new Car("porsche direct")};
    }

}
