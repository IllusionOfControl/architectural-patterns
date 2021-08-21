#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <map>


class CryptManager {
public:
	virtual std::string RequestCrypt(std::string expression) {
		std::cout << "CryptManager: Crypt expression - " << expression << std::endl;

		int offset_value = 3;

		// from internet
		for (char& letter : expression) {
			if (letter >= 'a' && letter <= 'z') {
				letter = letter + offset_value;
				if (letter > 'z') {
					letter = letter - 'z' + 'a' - 1;
				}
			}
			if (letter >= 'A' && letter <= 'Z') {
				letter = letter + offset_value;
				if (letter > 'Z') {
					letter = letter - 'Z' + 'A' - 1;
				}
			}
		}

		return expression;
	}
};


class CachedCryptManager : public CryptManager {
private:
	std::map<std::string, std::string> _cache;
	CryptManager* _cryptManager;
public:
	CachedCryptManager() {
		_cryptManager = new CryptManager;
	}

	virtual std::string RequestCrypt(std::string expression) {
		std::string data;

		auto search = _cache.find(expression);
		if (search != _cache.end()) {
			std::cout << "CachedCryptManager: Use value from cache - " << expression << std::endl;
			data = search->second;
		}
		else {
			data = _cryptManager->RequestCrypt(expression);
			std::cout << "CachedCryptManager: Paste to cache - " << expression << std::endl;
			_cache[expression] = data;
		}
		return data;
	}
};


void ClientCode(CryptManager* manager) {
	manager->RequestCrypt("attempt_one");
	manager->RequestCrypt("attempt_two");
	manager->RequestCrypt("attempt_thre");
	manager->RequestCrypt("attempt_two");
}

int main() {
	CryptManager* manager = new CryptManager;
	CryptManager* cachedManager = new CachedCryptManager;

	std::cout << "=== CachedCryptManager" << std::endl;
	ClientCode(manager);

	std::cout << std::endl;

	std::cout << "=== CachedCryptManager" << std::endl;
	ClientCode(cachedManager);

	return 0;
}