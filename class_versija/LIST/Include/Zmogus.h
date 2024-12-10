#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus {
protected:
    std::string vardas;
    std::string pavarde;

public:
    // Konstruktoriai
    Zmogus() : vardas(""), pavarde("") {}
    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas(vardas), pavarde(pavarde) {}

    // Destruktorius
    virtual ~Zmogus() {
        vardas.clear();
        pavarde.clear();
    }

    // Get ir Set metodai
    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    void setVardas(const std::string& vardas) { this->vardas = vardas; }
    void setPavarde(const std::string& pavarde) { this->pavarde = pavarde; }

    // Grynai virtuali funkcija
    virtual void printInfo() const = 0;
};

#endif // ZMOGUS_H
