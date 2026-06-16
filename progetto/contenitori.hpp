#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

//FIFO queue
template <typename T>
class fifo{
private:
    std::queue<T> dati;
public:
    fifo()=default;
    void put(const T& valore){
        dati.push(valore); //inserisce in fondo alla coda
    }
    T get() { 
        T val = dati.front(); // Recupera l'elemento in testa 
        dati.pop();           // Lo rimuove dalla coda
        return val; 
    }
    bool empty() const { 
        return dati.empty(); // Verifica se la coda è vuota 
    }     
};

//LIFO stack

template <typename T>
class lifo{
private:
    std::stack<T> dati;
public:
    lifo()=default;
    void put(const T& valore){
        dati.push(valore); //inserisce in cima alla pila
        return;
    }
    T get() { 
        T val = dati.top(); // Recupera l'elemento in testa 
        dati.pop();           // Lo rimuove dalla pila
        return val; 
    }
    bool empty() const { 
        return dati.empty(); // Verifica se la pila è vuota 
    }     
};