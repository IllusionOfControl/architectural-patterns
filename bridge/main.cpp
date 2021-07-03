#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>


class DbObject {
public:
    DbObject(std::string content) {
        _content = content;
    }

    std::string GetContent() {
        return _content;
    }

private:
    std::string _content;
};


class Database {
public:
    virtual void SaveObject(DbObject* obj) const = 0;
};


class ObjectRepository {
public:
    ObjectRepository(Database* database) {
        _database = database;
    }

    virtual Database* GetDatabase() {
        return _database;
    }

    virtual DbObject* CreateObject() = 0;

    virtual void SaveObject(DbObject* obj) const {
        _database->SaveObject(obj);
    }

private:
    Database* _database;
};


class ObjectRepositoryA : public ObjectRepository {
public:
    ObjectRepositoryA(Database* database) : ObjectRepository(database) {
    }

    virtual DbObject* CreateObject() {
        return new DbObject("Object A");
    }

    virtual void SaveObject(DbObject* obj) const {
        std::cout << "ObjectRepositoryA call database to save the \"" << obj->GetContent() << "\"" << std::endl;
        __super::SaveObject(obj);
    }
};


class ObjectRepositoryB : public ObjectRepository {
public:
    ObjectRepositoryB(Database* database) : ObjectRepository(database) {
    }

    virtual DbObject* CreateObject() {
        return new DbObject("Object B");
    }

    virtual void SaveObject(DbObject* obj) const {
        std::cout << "ObjectRepositoryB call database to save the \"" << obj->GetContent() << "\"" << std::endl;
        __super::SaveObject(obj);
    }
};


class RedisDatabase : public Database {
public:
    void SaveObject(DbObject* obj) const {
        std::cout << "Redis save the \"" << obj->GetContent() << "\"" << std::endl;
    }

};


class PostgresDatabase : public Database {
public:
    void SaveObject(DbObject* obj) const  {
        std::cout << "Postgres save the \"" << obj->GetContent() << "\"" << std::endl;
    }

};


void ClientCode(const ObjectRepository* repository, DbObject* dbObject) {
    repository->SaveObject(dbObject);
}


int main() {
    Database* database;
    ObjectRepository* repository;

    database = new RedisDatabase;
    repository = new ObjectRepositoryA(database);
    ClientCode(repository, repository->CreateObject());
    std::cout << std::endl;
    delete database;
    delete repository;

    database = new PostgresDatabase;
    repository = new ObjectRepositoryA(database);
    ClientCode(repository, repository->CreateObject());
    std::cout << std::endl;
    delete database;
    delete repository;

    database = new RedisDatabase;
    repository = new ObjectRepositoryB(database);
    ClientCode(repository, repository->CreateObject());
    std::cout << std::endl;
    delete database;
    delete repository;

    database = new PostgresDatabase;
    repository = new ObjectRepositoryB(database);
    ClientCode(repository, repository->CreateObject());
    std::cout << std::endl;
    delete database;
    delete repository;

    return 0;
}