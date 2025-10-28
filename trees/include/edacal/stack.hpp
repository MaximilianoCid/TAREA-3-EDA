#ifndef EDACAL_STACK_HPP
#define EDACAL_STACK_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace edacal {

// Pila generica basada en un vector que expone operaciones de insercion y
// extraccion con semantica LIFO. Se usa para los algoritmos de conversion y
// construccion del arbol en la calculadora.
template <typename T>
class Pila {
public:
    Pila() = default;

    // Inserta un nuevo elemento en la cima de la pila.
    template <typename U>
    void apilar(U&& value) {
        storage_.push_back(std::forward<U>(value));
    }

    // Obtiene una referencia al elemento en la cima de la pila.
    T& cima() {
        if (storage_.empty()) {
            throw std::out_of_range("Pila::cima en pila vacia");
        }
        return storage_.back();
    }

    // Version constante de top() para inspeccionar la cima sin modificarla.
    const T& cima() const {
        if (storage_.empty()) {
            throw std::out_of_range("Pila::cima en pila vacia");
        }
        return storage_.back();
    }

    // Extrae y devuelve el elemento superior.
    T desapilar() {
        if (storage_.empty()) {
            throw std::out_of_range("Pila::desapilar en pila vacia");
        }
        T value = std::move(storage_.back());
        storage_.pop_back();
        return value;
    }

    // Indica si no hay elementos almacenados.
    bool estaVacia() const {
        return storage_.empty();
    }

    // Cantidad de elementos actualmente almacenados.
    std::size_t tamano() const {
        return storage_.size();
    }

    // Elimina todos los elementos de la pila.
    void limpiar() {
        storage_.clear();
    }

private:
    std::vector<T> storage_;
};

} // namespace edacal

#endif // EDACAL_STACK_HPP
