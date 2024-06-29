#include <iostream>
#include <random>
#include "fibheap.h"

int main(){

    FibHeap heap1, heap2;

    const int32_t min = 0, max = 10000;

    std::random_device random_dev;
    std::mt19937 generator(random_dev());
    std::uniform_int_distribution distribution(min, max);

    int32_t p = distribution(generator);
    p *= p < 0 ? -1 : 1;
    p %= 100;
    ++p;

    for(uint32_t k=10; k<=100; k*=10)
        for(uint32_t N=1000; N<=10000000; N*=10){

            for(size_t i=0; i<N; ++i){

                int32_t generated_num1 = distribution(generator);
                int32_t generated_num2 = distribution(generator);

                heap1.insert(generated_num1);
                heap2.insert(generated_num2);


                if(i % k == 0){
                    heap1.extract_min();
                    heap2.extract_min();
                }

            }

            std::cout<<"-----------------------------------\n"
                     <<"N: "<<N<<" k: "<<k<<" p: "<<p<<std::endl;


            heap1.merge(&heap2);

            for(size_t i=0; i<p; ++i)
                std::cout<<"Min. sum "<<i+1<<": "
                         <<heap1.extract_min() + heap1.extract_min()<<std::endl;

            heap1.delete_heap();
        }

    return 0;

}
