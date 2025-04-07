#include <iostream>

#include <fstream>
#include <sstream>
#include <string.h>

#include <vector>
#include <map>
#include <random>

using namespace std;

class Animal {
    protected:
        string name;
        int age;
        string sex;
        string color;
        int weight;
        string birthDate;
        string origin;
        string arrivalDate;
        string animalID;
    public:
        Animal(string name, int age, string sex, string color, int weight, string birthDate, string origin, string arrivalDate, string animalID) {
            this->name = name;
            this->age = age;
            this->sex = sex;
            this->color = color;
            this->weight = weight;
            this->birthDate = birthDate;
            this->origin = origin;
            this->arrivalDate = arrivalDate;
            this->animalID = animalID;
        }

        string getName() { return this->name; }
        int getAge() { return this->age; }
        string getSex() { return this->sex; }
        string getColor() { return this->color; }
        int getWeight() { return this->weight; }
        string getBirthDate() { return this->birthDate; }
        string getOrigin() { return this->origin; }
        string getArrivalDate() { return this->arrivalDate; }
        string getAnimalID() { return this->animalID; }

        virtual string getSpecies() { }

        string toString() {
            return this->animalID + "; " + 
            this->name + "; birth date: " + 
            this->birthDate + "; " + 
            this->color + "color; " + 
            to_string(this->weight) + " pounds; from " + 
            this->origin + "; arrived: " + 
            this->arrivalDate;
        }
};

class Hyena : public Animal {
    public:
        Hyena(string name, int age, string sex, string color, int weight, string birthDate, string origin, string arrivalDate, string animalID) : 
        Animal(name, age, sex, color, weight, birthDate, origin, arrivalDate, animalID) { }

        string getSpecies() override {
            return "Hyena";
        }
};

class Lion : public Animal {
    public:
        Lion(string name, int age, string sex, string color, int weight, string birthDate, string origin, string arrivalDate,  string animalID) : 
        Animal(name, age, sex, color, weight, birthDate, origin, arrivalDate, animalID) { }

        string getSpecies() override {
            return "Lion";
        }
};

class Tiger : public Animal {
    public:
        Tiger(string name, int age, string sex, string color, int weight, string birthDate, string origin, string arrivalDate,  string animalID) : 
        Animal(name, age, sex, color, weight, birthDate, origin, arrivalDate, animalID) { }

        string getSpecies() override {
            return "Tiger";
        }
};

class Bear : public Animal {
    public:
        Bear(string name, int age, string sex, string color, int weight, string birthDate, string origin, string arrivalDate,  string animalID) : 
        Animal(name, age, sex, color, weight, birthDate, origin, arrivalDate, animalID) { }

        string getSpecies() override {
            return "Bear";
        }
};

vector<string> splitBySpace(const string& str) {
    vector<string> result;
    stringstream strStream(str);
    string word;

    while (strStream >> word) {
        result.push_back(word);
    }

    return result;
}

string genAnimalName(string& species) {
    string line;
    string fileName = "text files/animalNames.txt";
    ifstream namesFile(fileName);

    vector<string> names;
    bool foundSpecies = false;

    while (getline(namesFile, line)) {
        if (line.find(species + " Names:") != string::npos) {
            foundSpecies = true;
            continue;
        }
        if (foundSpecies) {
            if (line.empty()) 
                continue;

            size_t pos = 0;
            while ((pos = line.find(",")) != string::npos) {
                names.push_back(line.substr(0, pos));
                line.erase(0, pos + 2);
            }
            if (!line.empty())
                names.push_back(line);
            break;
        }
    }

    namesFile.close();
    static default_random_engine rng;
    uniform_int_distribution<size_t> distribution(0, names.size() - 1);

    return names[distribution(rng)];
}

// Method to generate a birthday based on the season and age of the animal
string genAnimalBirthday(string season, int age) {
    static default_random_engine rng;
 		
    int currentYear = 2025;
    int birthYear = currentYear - age;
    int birthDay;
    int birthMonth;
    
    // Generate a random Month dependent on the season.
    if (season == "Spring") {
        uniform_int_distribution<size_t> distribution(1, 3);
        birthMonth = distribution(rng);
    }
    else if (season == "Summer") {
        uniform_int_distribution<size_t> distribution(4, 6);
        birthMonth = distribution(rng);
    }
    else if (season == "Fall") {
        uniform_int_distribution<size_t> distribution(7, 9);
        birthMonth = distribution(rng);
    }
    else if (season == "Winter") {
        uniform_int_distribution<size_t> distribution(10, 12);
        birthMonth = distribution(rng);
    }
    else
        birthMonth = 1;

    // Generate a random day dependent on the month
    // Even months up until August have 30 days
    // Odd months up until September have 31 days
    if (birthMonth == 2) {
        uniform_int_distribution<size_t> distribution(1, 28);
        birthDay = distribution(rng);
    }
    else if (birthMonth < 8) {
        if (birthMonth % 2 == 0) {
            uniform_int_distribution<size_t> distribution(1, 30);
            birthDay = distribution(rng);
        }
        else {
            uniform_int_distribution<size_t> distribution(1, 31);
            birthDay = distribution(rng);
        }
    }
    else if (birthMonth > 7) {
        if (birthMonth % 2 == 0) {
            uniform_int_distribution<size_t> distribution(1, 31);
            birthDay = distribution(rng);
        }
        else {
            uniform_int_distribution<size_t> distribution(1, 30);
            birthDay = distribution(rng);
        }
    }
    else
        birthDay = 1;
    
    // This might look like a lot of code to generate a birthday but that's only because it is.
    string finalBirthDay = to_string(birthYear);
    if (birthMonth < 10)
        finalBirthDay += "-0" + to_string(birthMonth);
    else
        finalBirthDay += "-" + to_string(birthMonth);
        
    if (birthDay < 10)
        finalBirthDay += "-0" + to_string(birthDay);
    else
        finalBirthDay += "-" + to_string(birthDay);
        
    return finalBirthDay; // Returns YYYY-MM-DD
}

// Method to generate an arrival date, effectively the same as genBirthDay()
string genArrivalDate(int age) {
    static default_random_engine rng;
 		
    int currentYear = 2025;
    int minimumYear = currentYear - age + 1;
    
    uniform_int_distribution<size_t> yearDistribution(minimumYear, currentYear);
    uniform_int_distribution<size_t> monthDistribution(1, 12);

    int arrivalYear = yearDistribution(rng);
    int arrivalMonth = monthDistribution(rng);
    int arrivalDay;
    
    if (arrivalMonth == 2) {
        uniform_int_distribution<size_t> distribution(1, 28);
        arrivalDay = distribution(rng);
    }
    else if (arrivalMonth < 8) {
        if (arrivalMonth % 2 == 0) {
            uniform_int_distribution<size_t> distribution(1, 30);
            arrivalDay = distribution(rng);
        }
        else {
            uniform_int_distribution<size_t> distribution(1, 31);
            arrivalDay = distribution(rng);
        }
    }
    else if (arrivalMonth > 7) {
        if (arrivalMonth % 2 == 0) {
            uniform_int_distribution<size_t> distribution(1, 31);
            arrivalDay = distribution(rng);
        }
        else {
            uniform_int_distribution<size_t> distribution(1, 30);
            arrivalDay = distribution(rng);
        }
    }
    else
        arrivalDay = 1;
    
    string arrivalDate = to_string(arrivalYear);
    if (arrivalMonth < 10)
        arrivalDate += "-0" + to_string(arrivalMonth);
    else
        arrivalDate += "-" + to_string(arrivalMonth);
        
    if (arrivalDay < 10)
        arrivalDate += "-0" + to_string(arrivalDay);
    else
        arrivalDate += "-" + to_string(arrivalDay);
    
    return arrivalDate;
}

void processAnimals(string& fileName, vector<Animal*>& animals, map<string, int>& speciesCount) {
    string parsedText;
    ifstream animalsFile(fileName);

    // Read file line by line
    while (getline(animalsFile, parsedText)) {
        vector<string> parts;
        stringstream strStream(parsedText);
        string item;

        // Split by commas
        while (getline(strStream, item, ',')) {
            // Remove any leading/trailing spaces from each part
            item.erase(0, item.find_first_not_of(" \t"));
            item.erase(item.find_last_not_of(" \t") + 1);
            parts.push_back(item);
        }

        // Now split each part by spaces and print the result
        int sectionNum = 0;

        // Variables to save information about the animal
        // (Note: season, color and origins are not used, they are there if needed for later)
        int age, weight;
        string name, sex, species, season, color, firstOrigin, secondOrigin;

        for (const auto& part : parts) {
            vector<string> splitWords = splitBySpace(part);

            switch (sectionNum) {
                case 0:
                    age = stoi(splitWords[0]); // Parse string as int
                    sex = splitWords[3];
                    species = splitWords[4];
                    break;
                case 1:
                    season = splitWords[2];
                    break;
                case 2:
                    for (const auto& word : splitWords) {
                        if (word != "color")
                            color += word + " ";
                    }
                    break;
                case 3:
                    weight = stoi(splitWords[0]); // Parse string as int
                    break;
                case 4:
                    for (const auto& word : splitWords) {
                        if (word != "from")
                            firstOrigin += word + " ";
                    }
                    break;
                case 5:
                    secondOrigin = splitWords[0];
                    break;
            }
            sectionNum++;
        }

        // Convert the first character of the species string to upper to be used later when generating report
        species[0] = toupper(species[0]);
        name = genAnimalName(species);
        string birthday = genAnimalBirthday(season, age);
        string arrivalDate = genArrivalDate(age);
        string animalID = "n/a";

        // Increase the species count for the given species
        speciesCount[species]++;

        // Push the respective animal species to the vector as their respective class
        if (species == "Hyena") {
            animalID = speciesCount.at(species) > 9 ? "Hy" + to_string(speciesCount.at(species)) : "Hy0" + to_string(speciesCount.at(species));
            animals.push_back(new Hyena(name, age, sex, color, weight, birthday, firstOrigin + secondOrigin, arrivalDate, animalID));
        }
        if (species == "Lion") {
            animalID = speciesCount.at(species) > 9 ? "Li" + to_string(speciesCount.at(species)) : "Li0" + to_string(speciesCount.at(species));
            animals.push_back(new Lion(name, age, sex, color, weight, birthday, firstOrigin + secondOrigin, arrivalDate,  animalID));
        }
        if (species == "Tiger") {
            animalID = speciesCount.at(species) > 9 ? "Ti" + to_string(speciesCount.at(species)) : "Ti0" + to_string(speciesCount.at(species));
            animals.push_back(new Tiger(name, age, sex, color, weight, birthday, firstOrigin + secondOrigin, arrivalDate,  animalID));
        }
        if (species == "Bear") {
            animalID = speciesCount.at(species) > 9 ? "Be" + to_string(speciesCount.at(species)) : "Be0" + to_string(speciesCount.at(species));
            animals.push_back(new Bear(name, age, sex, color, weight, birthday, firstOrigin + secondOrigin, arrivalDate,  animalID));
        }
    }

    // Close the file.
    animalsFile.close();
}

void genReport(vector<Animal*>& animals, map<string, int>& speciesCount) {
    // Create a new map to optimize code performance
    map<string, vector<Animal*>> speciesMap;

    // Get each animals species and push that animal back into the map
    for (const auto& animal : animals) {
        speciesMap[animal->getSpecies()].push_back(animal);
    }

    string outputFileName = "text files/newAnimals.txt";
    ofstream file(outputFileName);

    // Iterate over each species inside the count
    for (const auto& count : speciesCount) {
        file << count.first << "Habitat: " << endl;

        // Iterate over each animal inside the species map
        for (const auto& animal : speciesMap[count.first]) {
            file << animal->toString() << endl;
        }

        file << endl;
    }
}

int main() {
    vector<Animal*> animals;
    map<string, int> speciesCount;
    string animalsFile = "text files/arrivingAnimals.txt";

    processAnimals(animalsFile, animals, speciesCount);
    genReport(animals, speciesCount);

    // Delete animal instances to free up memory
    for (Animal* animal : animals)
        delete animal;
    
    cout << "Code Executed in 7 hours" << endl;
    return 0;
}