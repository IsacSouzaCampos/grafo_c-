#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions


namespace structures {
template<typename T>
//! lista encadeada
class LinkedList {
 public:
     //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        //! coment
        explicit Node(const T& data):
        data_{data}
        {}

        //! Construtor de um node completo.
        explicit Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        //! Getter do dado
        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }
        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;  // data_
        Node* next_{nullptr};  // next_
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* before_index(std::size_t index) {  // node anterior ao index
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    void insert(const T& data, Node* before);  // inserir na posicao polimorfico

    Node* head{nullptr};  // head
    std::size_t size_{0u};  // size_
};

template<typename T>
LinkedList<T>::LinkedList() {}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void LinkedList<T>::clear() {
    while (!empty())
        pop_front();
}

template<typename T>
void LinkedList<T>::push_back(const T& data) {
    try {
        insert(data, size_);
    } catch(std::out_of_range error) {
        throw error;
    }
}

template<typename T>
void LinkedList<T>::push_front(const T& data) {
    Node* novoElemento = new Node(data);
    if (novoElemento == nullptr)
        throw std::out_of_range("lista cheia");

    novoElemento->next(head);
    head = novoElemento;
    size_++;
}

template<typename T>
void LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("index invalido");

    if (index == 0) {
        push_front(data);
    } else {
        Node* novoElemento = new Node(data);
        if (novoElemento == nullptr)
            throw std::out_of_range("lista cheia");

        Node* elementoAnterior = before_index(index);
        Node* proximoElemento = elementoAnterior->next();
        novoElemento->next(proximoElemento);
        elementoAnterior->next(novoElemento);
        size_++;
    }
}

template<typename T>
void LinkedList<T>::insert(const T& data, Node* before) {
    Node* novoElemento = new Node(data);
    if (novoElemento == nullptr)
        throw std::out_of_range("lista cheia");

    novoElemento->next(before->next());
    before->next(novoElemento);
    size_++;
}

template<typename T>
void LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* elementoAtual = head;
        Node* elementoAnterior = head;
        int posicao = size();
        for (int i = 0; i < size(); ++i) {
            if (!(data > elementoAtual->data())) {
                posicao = i;
                break;
            }
            elementoAnterior = elementoAtual;
            elementoAtual = elementoAtual->next();
        }
        posicao == 0? push_front(data) : insert(data, elementoAnterior);
    }
}

template<typename T>
T LinkedList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("index invalido");

    Node* current = index == 0? head : before_index(index)->next();
    return current->data();
}

template<typename T>
T LinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("lista vazia");
    if (index >= size())
        throw std::out_of_range("index invalido");

    if (!index)
        return pop_front();

    Node* anterior = before_index(index);
    Node* elemento = anterior->next();
    T data = elemento->data();
    anterior->next(elemento->next());
    size_--;
    delete elemento;
    return data;
}

template<typename T>
T LinkedList<T>::pop_back() {
    try {
        return pop(size_ - 1);
    } catch(std::out_of_range error) {
        throw error;
    }
}

template<typename T>
T LinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("lista vazia");

    Node* elemento = head;
    T data = elemento->data();
    head = elemento->next();
    size_--;
    delete elemento;
    return data;
}

template<typename T>
void LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool LinkedList<T>::empty() const {
    return !size_;
}

template<typename T>
bool LinkedList<T>::contains(const T& data) const {
    if (empty())
        throw std::out_of_range("lista vazia");
    Node *elemento = head;
    while (elemento != nullptr) {
        if (elemento->data() == data)
            return true;
        elemento = elemento->next();
    }
    return false;
}

template<typename T>
std::size_t LinkedList<T>::find(const T& data) const {
    int i = 0;
    Node* elemento = head;
    while (i < size()) {
        if (elemento->data() == data)
            break;
        elemento = elemento->next();
        i++;
    }
    return i;
}

template<typename T>
std::size_t LinkedList<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
