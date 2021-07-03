#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

class TextFile {
public:
    virtual std::string GetText() const {
        return "Text from file \n";
    }
};


class PdfFile {
public:
    virtual std::string RecognizePage(int page) {
        char buf[32];
        std::sprintf(buf, "Text from page %d \n", page);
        return std::string(buf);
    };
};


class PdfToTextAdapter : public TextFile {
private:
    PdfFile* _pdfFile;
public:
    PdfToTextAdapter(PdfFile* pdfFile) {
        _pdfFile = pdfFile;
    }

    virtual std::string GetText() const {
        std::string text = "Text from document \n";
        for (int i = 0; i < 10; i++) {
            text.append(_pdfFile->RecognizePage(i));
        }
        return text;
    }
};

void ClientCode(const TextFile* file) {
    std::cout << file->GetText();
}

int main() {
    TextFile* textFile = new TextFile;
    ClientCode(textFile);
    std::cout << "\n";

    PdfFile* pdfFile = new PdfFile;
    PdfToTextAdapter* pdfAdapter = new PdfToTextAdapter(pdfFile);
    ClientCode(pdfAdapter);
    std::cout << "\n";
    return 0;
}