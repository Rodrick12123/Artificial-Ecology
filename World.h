#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class OrgWorld : public emp::World<Organism>
{

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

public:
    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random)
    {
        random_ptr.New(_random);
    }

    ~OrgWorld()
    {
    }
    // updates organims reproduction status
    void Update()
    {
        // emp::World<Organism>::Update();
        std::cout << "Updating!" << std::endl; // feel free to get rid of this

        for (int i = 0; i < GetSize(); i++)
        {

            if (!IsOccupied(i))
            {
                continue;
            }
            else
            {
                Organism *p = pop[i];
                if (p->getSpecies() == 1)
                {
                    // needs a much higher reproduction rate
                    p->Process(500);
                }
            }
        }

        emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
        for (int i : schedule)
        {
            // do stuff
            emp::Ptr<Organism> offspring;
            if (IsOccupied(i))
            {
                offspring = pop[i]->CheckReproduction();
            }
            // emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
            if (offspring)
            {
                DoBirth(*offspring, i); // i is the parent's position in the world
            }
        }
    }

    // moves organisms around the field
    void moveOrg()
    {

        for (int i = 0; i < GetSize(); i++)
        {

            if (IsOccupied(i))
            {

                Organism *org = ExtractOrganism(i);
                std::cout << "\nCurrent speciesa: " << org->getSpecies() << std::endl;
                emp::WorldPosition position = GetRandomNeighborPos(i);
                // space is open
                if (!IsOccupied(position))
                {
                    AddOrgAt(org, position);
                }
                else if (IsOccupied(position) && org->getSpecies() == 2)
                {
                    // check orgs species at position
                    size_t id = position.GetIndex();
                    Organism org2 = GetOrg(id);
                    // canibal cases
                    if (org2.getSpecies() != 2)
                    {
                        std::cout << "\nCurrent speciesz: " << org2.getSpecies() << std::endl;
                        RemoveOrgAt(position);
                        AddOrgAt(org, position);
                        org->Process(500);
                        org->AddEnergy(500);
                    }
                }
                if (org->getSpecies() == 2)
                {
                    // all species 2 loose energy and die
                    org->SubEnergy(10);
                    std::cout << "\nCurrent Energy: " << org->getEnergy() << std::endl;

                    if (org->getEnergy() <= 0)
                    {
                        RemoveOrgAt(position);
                    }
                }
            }
        }
    }

    Organism *ExtractOrganism(int i)
    {
        Organism *p = pop[i];
        pop[i] = nullptr;
        return p;
    }
};
#endif