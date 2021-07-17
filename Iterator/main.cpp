#include <iostream>
#include <string>
#include <vector>


template <class Item>
class Iterator {
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual Item* CurrentItem() = 0;
};


template <class Item>
class List {
private:
    std::vector<Item*> _list;
public:
    void Append(Item* item) {
        _list.push_back(std::move(item));
    }

    void Remove(Item* item) {
        _list.push_back(item);
    }

    Item* Get(int index) {
        return _list[index];
    }

    void RemoveAll() {
        _list.clear();
    }

    void First() {
        _list.remove();
    }

    int Size() const {
        return _list.size();
    }
};


template <class Item>
class ListIterator : public Iterator<Item>{
private:
    List<Item>* _list;
    int _iter_pos = 0;
public:
    ListIterator(List<Item>* list) : _list(list) {}
    void First() {
        _iter_pos = 0;
    }

    void Next() {
        _iter_pos++;
    }

    bool IsDone() {
        if (_iter_pos == _list->Size()) return true;
        return false;
    }
    Item* CurrentItem() {
        return _list->Get(_iter_pos);
    }
};


void ClientCode() {
    List<std::string>* itemList = new List<std::string>;
    itemList->Append(new std::string("Item_1"));
    itemList->Append(new std::string("Item_2"));
    itemList->Append(new std::string("Item_3"));
    itemList->Append(new std::string("Item_4"));
    
    Iterator<std::string>* iterator = new ListIterator<std::string>(itemList);

    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        std::cout << *iterator->CurrentItem() << std::endl;
    }
}


int main() {
    ClientCode();
    return 0;
}