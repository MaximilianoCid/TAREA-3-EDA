#ifndef EDACAL_STACK_HPP
#define EDACAL_STACK_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace edacal {

template <typename T>
class Pila {
public:
    Pila() = default;
    template <typename U>
    void apilar(U&& value) {
        storage_.push_back(std::forward<U>(value));
    }
    
    T& cima() {
        if (storage_.empty()) {
            throw std::out_of_range("Pila::cima en pila vacia");
        }
        return storage_.back();
    }

    const T& cima() const {
        if (storage_.empty()) {
            throw std::out_of_range("Pila::cima en pila vacia");
        }
        return storage_.back();
    }

    T desapilar() {
        if (storage_.empty()) {
            throw std::out_of_range("Pila::desapilar en pila vacia");
        }
        T value = std::move(storage_.back());
        storage_.pop_back();
        return value;
    }

    bool estaVacia() const {
        return storage_.empty();
    }

    std::size_t tamano() const {
        return storage_.size();
    }

    void limpiar() {
        storage_.clear();
    }

private:
    std::vector<T> storage_;
};

} 

#endif 
