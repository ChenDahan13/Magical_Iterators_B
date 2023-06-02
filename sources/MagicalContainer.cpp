#include "MagicalContainer.hpp"

using namespace std;
using namespace ariel;

void MagicalContainer::copyContainer(vector<int>& container, vector<int>& other) {
    for(std::vector<int>::size_type i = 0; i < other.size(); i++) {
        container.push_back(other[i]);
    }
}

MagicalContainer::MagicalContainer(MagicalContainer& other) {
    this->copyContainer(this->originalContainer, other.originalContainer);
    this->copyContainer(this->ascendingContainer, other.ascendingContainer);
    this->copyContainer(this->primeContainer, other.primeContainer);
    this->copyContainer(this->sideCrossContainer, other.sideCrossContainer);
}

/* MagicalContainer Functions */
void MagicalContainer::addAscending(int element) {
    
    if(this->ascendingContainer.empty()) { // First element
        this->ascendingContainer.push_back(element);
    } else {
        int added = 0, addposition = 0;
        for(std::vector<int>::size_type i = 0; i < this->ascendingContainer.size(); i++) {
            if(!added && element < this->ascendingContainer[i]) { // Found place to add
                this->ascendingContainer.insert(this->ascendingContainer.begin() + addposition, element);
                added = 1;
            }
            addposition++;
        }

        if(!added) { // Adds to the end
            this->ascendingContainer.push_back(element);
        }
    }
}

MagicalContainer& MagicalContainer::operator=(MagicalContainer& other) {
    if(this != &other) {
        this->originalContainer.clear();
        this->ascendingContainer.clear();
        this->primeContainer.clear();
        this->sideCrossContainer.clear();
        this->copyContainer(this->originalContainer, other.originalContainer);
        this->copyContainer(this->ascendingContainer, other.ascendingContainer);
        this->copyContainer(this->primeContainer, other.primeContainer);
        this->copyContainer(this->sideCrossContainer, other.sideCrossContainer);
    }
    return *this;
}

void MagicalContainer::updateSideCross() {
    
    this->sideCrossContainer.clear();
    
    vector<int>::iterator start = this->originalContainer.begin();
    vector<int>::iterator end = this->originalContainer.end() - 1;

    bool addStart = true;

    for(int i = 0; i < this->originalContainer.size(); i++) {
        if(addStart) { 
            this->sideCrossContainer.push_back(*start);
            start++;
        } else { 
            this->sideCrossContainer.push_back(*end);
            end--;
        }
        addStart = !addStart;
    }
}

void MagicalContainer::addElement(int element) {
    
    this->originalContainer.push_back(element);
    
    if(isPrime(element)) { // Add to primeContainer
        printf("Adding %d to primeContainer\n", element);
        this->primeContainer.push_back(element);
    }

    this->addAscending(element); // Add to ascendingContainer
    this->updateSideCross(); // Update sideCrossContainer
}

int MagicalContainer::size() {
    return this->originalContainer.size();
}

bool MagicalContainer::isPrime(int element) {
    if (element <= 1) {
        return false;
    }
    for (int i = 2; i <= element / 2; i++) {
        if (element % i == 0) {
            return false;
        }
    }
    return true;
}

void MagicalContainer::deleteElement(vector<int>& container, int element) {
    int addposition = 0;
    int isDeleted = 0;
    for(std::vector<int>::size_type i = 0; i < container.size(); i++) {
        if(container[i] == element) {
            container.erase(container.begin() + addposition);
            isDeleted = 1;
        }
        addposition++;
    }

    if(!isDeleted) {
        throw runtime_error("Element not found");
    }
}

void MagicalContainer::removeElement(int element) {
    this->deleteElement(this->originalContainer, element);
    this->deleteElement(this->ascendingContainer, element);
    if(isPrime(element))
        this->deleteElement(this->primeContainer, element);
    this->deleteElement(this->sideCrossContainer, element);
}
/* -------------------------- */


/*/////////////////////////////*/
/* Iterators Classes Functions */
/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


/* AscendingIterator Functions */
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container): container(&container){
    this->ptr = this->container->ascendingContainer.begin();
}

MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator& other): container(other.container) {
    this->ptr = this->container->ascendingContainer.begin();
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    bool b = this->operator==(other);
    if(b) {
        return false;
    } else {
        return true;
    }
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    
    if(this->container != other.container) {
        throw invalid_argument("Iterators are not from the same container");
    }

    if(this->ptr == other.ptr) {
        return true;
    } else {
        return false;
    }

}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    
    if(this->container != other.container) {
        throw invalid_argument("Iterators are not from the same container");
    }
    
    if(this->ptr < other.ptr) {
        return true;
    } else {
        return false;
    }
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    
    if(this->container != other.container) {
        throw invalid_argument("Iterators are not from the same container");
    }
    
    if(this->ptr > other.ptr) {
        return true;
    } else {
        return false;
    }
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {

    if(this->container != other.container) {
        throw runtime_error("Iterators are not from the same container");
    }

    if(this != &other) {
        this->container = other.container;
        this->ptr = other.ptr;
    }
    return *this;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    if(this->ptr == this->container->ascendingContainer.end()) {
        throw runtime_error("Iterator is at the end of the container");
    }

    this->ptr++;
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() const {
   if(this->ptr == this->container->ascendingContainer.end()) {
        throw runtime_error("Iterator is at the end of the container");
    }
    return *this->ptr;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    AscendingIterator ai(*this);
    return ai;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    AscendingIterator ai(*this);
    ai.ptr = this->container->ascendingContainer.end();
    return ai;
}
/* -------------------------- */


/* SideCrossIterator Functions */
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container): container(&container) {
    this->ptr = this->container->sideCrossContainer.begin();
}

MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator& other): container(other.container) {
    this->ptr = this->container->sideCrossContainer.begin();
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    bool b = this->operator==(other);
    if(b) {
        return false;
    } else {
        return true;
    }
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    if(this->container != other.container) {
        throw invalid_argument("Iterators are not from the same container");
    }

    if(this->ptr == other.ptr) {
        return true;
    } else {
        return false;
    }
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
    if(this->container != other.container) {
        throw invalid_argument("Iterators are not from the same container");
    }

    if(this->ptr < other.ptr) {
        return true;
    } else {
        return false;
    }
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
    if(this->container != other.container) {
        throw invalid_argument("Iterators are not from the same container");
    }

    if(this->ptr > other.ptr) {
        return true;
    } else {
        return false;
    }
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if(this->container != other.container) {
        throw runtime_error("Iterators are not from the same container");
    }

    if(this != &other) {
        this->container = other.container;
        this->ptr = other.ptr;
    }
    return *this;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if(this->ptr == this->container->sideCrossContainer.end()) {
        throw runtime_error("Iterator is at the end of the container");
    }

    this->ptr++;
    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const {
    if(this->ptr == this->container->sideCrossContainer.end()) {
        throw runtime_error("Iterator is at the end of the container");
    }
    return *this->ptr;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    SideCrossIterator sci(*this);
    return sci;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    SideCrossIterator sci(*this);
    sci.ptr = this->container->sideCrossContainer.end();
    return sci;
}

/* -------------------------- */


/* PrimeIterator Functions */
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container): container(&container){
    this->ptr = this->container->primeContainer.begin();
}

MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator& other): container(other.container) {
    this->ptr = this->container->primeContainer.begin();
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    bool b = this->operator==(other);
    if(b) {
        return false;
    } else {
        return true;
    }
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
    if(this->container != other.container) {
        throw invalid_argument("Iterators are not from the same container");
    }

    if(this->ptr == other.ptr) {
        return true;
    } else {
        return false;
    }
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
    if(this->container != other.container) {
        throw invalid_argument("Iterators are not from the same container");
    }

    if(this->ptr < other.ptr) {
        return true;
    } else {
        return false;
    }
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
    if(this->container != other.container) {
        throw invalid_argument("Iterators are not from the same container");
    }

    if(this->ptr > other.ptr) {
        return true;
    } else {
        return false;
    }
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if(this->container != other.container) {
        throw runtime_error("Iterators are not from the same container");
    }

    if(this != &other) {
        this->container = other.container;
        this->ptr = other.ptr;
    }
    return *this;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    if(this->ptr == this->container->primeContainer.end()) {
        throw runtime_error("Iterator is at the end of the container");
    }

    this->ptr++;
    return *this;
}

int MagicalContainer::PrimeIterator::operator*() const {
    if(this->ptr == this->container->primeContainer.end()) {
        throw runtime_error("Iterator is at the end of the container");
    }
    return *this->ptr;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    PrimeIterator pi(*this);
    return pi;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    PrimeIterator pi(*this);
    pi.ptr = this->container->primeContainer.end();
    return pi;
}
/* -------------------------- */