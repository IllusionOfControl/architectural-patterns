#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <typeinfo>


class TcpState;
class TcpConnected;
class TcpClosed;


class TcpConnection {
private:
    TcpState* _state;

public:
    TcpConnection(TcpState* state) : _state(nullptr) {
        ChangeState(state);
    }   

    void ChangeState(TcpState* state);

    void Open();

    void Close();

    void Send(const char* data);
};


class TcpState {
protected:
    TcpConnection* _connection;
public:
    void SetConnection(TcpConnection* connection) {
        _connection = connection;
    }

    virtual void Open() = 0;
    virtual void Close() = 0;
    virtual void Send(const char* data) = 0;
};


void TcpConnection::ChangeState(TcpState* state) {
    _state = state;
    _state->SetConnection(this);
}


void TcpConnection::Open() {
    _state->Open();
}


void TcpConnection::Close() {
    _state->Close();
}


void TcpConnection::Send(const char* data) {
    _state->Send(data);
}


class TcpClosed : public TcpState {
public:
    TcpClosed() {}

    void Open() {
        std::cout << "Connection is closed" << std::endl;
    }

    void Close() {
        std::cout << "Connection is closed" << std::endl;
    }

    void Send(const char* data) {
        std::cout << "Connection already is closed" << std::endl;
    }
};


class TcpConnected : public TcpState {
public:
    TcpConnected() {}

    void Open() {
        std::cout << "Connection is already opened" << std::endl;
    }

    void Close() {
        _connection->ChangeState(new TcpClosed);
    }

    void Send(const char* data) {
        std::cout << "Sended data: \t " << data << std::endl;
    }
};


void ClientCode() {
    TcpConnection* conn = new TcpConnection(new TcpConnected);
    conn->Open();
    conn->Send("Work!");
    conn->Close();
    conn->Send("Dont work!");
}

int main() {
    ClientCode();
    return 0;
}