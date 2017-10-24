#include <iostream>
#include <cstring>

using namespace std;

class Drinkable {
private:
    char* brand;
    int quantity;
public:
    Drinkable () {
        quantity = 0;
        brand=NULL;
    }

    Drinkable (Drinkable const &drnk) {
            setQuantity(drnk.getQuantity());
            setBrand(drnk.getBrand());

    }

    Drinkable &operator= (Drinkable const &drnk) {
        if (this != &drnk) {
            setQuantity(drnk.getQuantity());
            setBrand(drnk.getBrand());
        }

        return *this;
    }

    ~Drinkable () {
        delete[] brand;
    }

    void setQuantity(int newQuantity) {
        if(newQuantity>=0)
            quantity = newQuantity;

    }

    int const getQuantity() const {
        return quantity;
    }

    char const &operator[](int index)const{
        return brand[index];
    }

    char* const getBrand() const {
        return brand;
    }

    void setBrand(char const* newBrand) {
        if(brand!=NULL)
            delete[] brand;
        brand = new char[strlen(newBrand)+1];
        strcpy(brand, newBrand);
    }

    friend ostream& operator<< (ostream &output, Drinkable const& drnk) {
        if(drnk.brand==NULL)
            return output;
        for (int i = 0; i < strlen(drnk.getBrand()); ++i) {
            output << drnk[i];
        }

        output << " " << drnk.getQuantity();

        return output;
    }
};

int main ()
{
    Drinkable drink;

    drink.setBrand("fanta");
    drink.setQuantity(2);
    drink.setBrand("derbyy");
    cout<<drink<<endl;
    Drinkable kola;
    cout<<kola<<endl;

    return 0;
}
