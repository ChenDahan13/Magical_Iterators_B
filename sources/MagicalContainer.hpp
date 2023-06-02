#pragma once
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

namespace ariel {
}

    class MagicalContainer {

        vector<int> originalContainer;
        vector<int> ascendingContainer;
        vector<int> primeContainer; 
        vector<int> sideCrossContainer;

        void addAscending(int element);
        void updateSideCross();
        void deleteElement(vector<int>& container, int element);
        void copyContainer(vector<int>& container, vector<int>& other);

        public:  
            
            /* MagicalContainer Functions */
            MagicalContainer() = default;
            ~MagicalContainer() = default;
            MagicalContainer(MagicalContainer& other);
            MagicalContainer(MagicalContainer&& other) = default;
            MagicalContainer& operator=(MagicalContainer&& other) = default;
            MagicalContainer& operator=(MagicalContainer& other);
            
            void addElement(int element);
            void removeElement(int element);
            static bool isPrime(int element);
            int size();
            /* -------------------------- */

            
            /*///////////////////*/
            /* Iterators Classes */
            /*\\\\\\\\\\\\\\\\\\\*/
   
        class AscendingIterator {
                MagicalContainer* container;
                vector<int>::iterator ptr;
            
                public:
                    
                    AscendingIterator(MagicalContainer& container);
                    AscendingIterator(AscendingIterator& other);
                    AscendingIterator(AscendingIterator&& other) = default;
                    ~AscendingIterator() = default;
                    
                    bool operator!=(const AscendingIterator& other) const;
                    bool operator==(const AscendingIterator& other) const;
                    bool operator<(const AscendingIterator& other) const;
                    bool operator>(const AscendingIterator& other) const;
                    
                    AscendingIterator& operator=(AscendingIterator&& other) = default;
                    AscendingIterator& operator=(const AscendingIterator& other);
                    AscendingIterator& operator++();
                    int operator*() const;
                
                    AscendingIterator begin();
                    AscendingIterator end();

        };

        class SideCrossIterator {
            MagicalContainer* container;
            vector<int>::iterator ptr;

            public:
                
                SideCrossIterator(MagicalContainer& container);
                SideCrossIterator(SideCrossIterator& other);
                SideCrossIterator(SideCrossIterator&& other) = default;
                ~SideCrossIterator() = default;
                            
                bool operator!=(const SideCrossIterator& other) const;
                bool operator==(const SideCrossIterator& other) const;
                bool operator<(const SideCrossIterator& other) const;
                bool operator>(const SideCrossIterator& other) const;
            
                SideCrossIterator& operator=(SideCrossIterator&& other) = default;
                SideCrossIterator& operator=(const SideCrossIterator& other);
                SideCrossIterator& operator++();
                int operator*() const;

                SideCrossIterator begin();
                SideCrossIterator end();

        };

        class PrimeIterator {
            MagicalContainer* container;
            vector<int>::iterator ptr;
            
            public:
                    
                PrimeIterator(MagicalContainer& container);
                PrimeIterator(PrimeIterator& other);
                PrimeIterator(PrimeIterator&& other) = default;
                ~PrimeIterator() = default;
                                    
                bool operator!=(const PrimeIterator& other) const;
                bool operator==(const PrimeIterator& other) const;
                bool operator<(const PrimeIterator& other) const;
                bool operator>(const PrimeIterator& other) const;
                
                PrimeIterator& operator=(PrimeIterator&& other) = default;
                PrimeIterator& operator=(const PrimeIterator& other);
                PrimeIterator& operator++();
                int operator*() const;
            
                PrimeIterator begin();
                PrimeIterator end();

        };
    
    };

    
    
        



