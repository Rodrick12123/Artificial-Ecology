#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism
{
private:
    double points;
    int species;
    int energy;
    int evol;
    emp::Ptr<emp::Random> random;

public:
    Organism(emp::Ptr<emp::Random> _random, double _points = 0.0) : points(_points), random(_random) { ; }

    void SetPoints(double _in) { points = _in; }
    void AddPoints(double _in) { points += _in; }
    void SetSpecies(double _in) { species = _in; }
    void SetEvol(int _in) { evol = _in; }
    // void SubEnergy(double _in) { energy -= _in; }

    void Process(int point)
    {
        std::cout << "Processing" << std::endl; // feel free to get rid of this
        std::cout << "Current speciesp: " << species << std::endl;
        AddPoints(point);
    }

    void SubEnergy(int e)
    {
        std::cout << "SubEnergy" << std::endl; // loose energy
        energy -= e;
    }

    void AddEnergy(int e)
    {
        std::cout << "AddEnergy" << std::endl; // species 2 gains energy
        energy += e;
    }

    int getEnergy()
    {
        return energy;
    }
    // check species
    int getSpecies()
    {
        return species;
    }
    int getEvol()
    {
        return evol; // checks speices 2 is evolved
    }

    emp::Ptr<Organism> CheckReproduction()
    {

        if (points >= 1000 && species == 2)
        {
            // create evolved offspring
            points -= 1000;
            emp::Ptr<Organism> offspring = new Organism(*this);
            offspring->SetSpecies(this->getSpecies());
            offspring->SetEvol(1);
            return offspring;
        }
        else if (points >= 500 && species == 2)
        {
            // species 2 is not evolved
            points -= 500;
            emp::Ptr<Organism> offspring = new Organism(*this);
            offspring->SetSpecies(this->getSpecies());
            offspring->SetEvol(0);
            return offspring;
        }
        else if (points >= 500 && species == 1)
        {
            // species 1 condition for reproduction
            points -= 500;
            emp::Ptr<Organism> offspring = new Organism(*this);
            offspring->SetSpecies(this->getSpecies());
            offspring->SetEvol(0);
            return offspring;
        }

        return nullptr;
    }
};
#endif