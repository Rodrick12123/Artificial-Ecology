

#include <iostream>
#include "emp/base/vector.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

#include "World.h"
#include "Org.h"
#include "Empirical/include/emp/math/Random.hpp"

emp::web::Document doc{"target"};

class AEAnimate : public emp::web::Animate
{

    // grid width and height
    const int num_h_boxes = 60;
    const int num_w_boxes = 60;
    const double RECT_SIDE = 5;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::Random random{5};
    OrgWorld world{random}; // whats wrong w this
    // where we'll draw
    emp::web::Canvas canvas{width, height, "canvas"};

public:
    AEAnimate()
    {

        // shove canvas into the div
        // along with some control buttons
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        // fill the vectors with 0 to start

        Organism *new_org = new Organism(&random);
        new_org->SetSpecies(1);
        world.AddOrgAt(new_org, 0);

        Organism *new_org1 = new Organism(&random);
        new_org1->SetSpecies(1);
        world.AddOrgAt(new_org1, 50);

        Organism *new_org3 = new Organism(&random);
        new_org3->SetSpecies(1);
        world.AddOrgAt(new_org3, 60);

        Organism *new_org4 = new Organism(&random);
        new_org4->SetSpecies(1);
        world.AddOrgAt(new_org4, 30);

        Organism *pred1 = new Organism(&random);
        pred1->SetSpecies(2);
        world.AddOrgAt(pred1, 5);
        pred1->AddEnergy(1000);

        Organism *pred2 = new Organism(&random);
        pred2->SetSpecies(2);
        world.AddOrgAt(pred2, 65);
        pred2->AddEnergy(1000);

        Organism *pred3 = new Organism(&random);
        pred3->SetSpecies(2);
        world.AddOrgAt(pred3, 55);
        pred3->AddEnergy(1000);

        Organism *pred4 = new Organism(&random);
        pred4->SetSpecies(2);
        world.AddOrgAt(pred4, 35);
        pred4->AddEnergy(1000);

        world.Resize(60, 60);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
        // showing how to set a cell to 'alive'
    }

    void DoFrame() override
    {

        canvas.Clear();
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++)
        {
            for (int y = 0; y < num_h_boxes; y++)
            {
                if (world.IsOccupied(org_num))
                {
                    Organism p = world.GetOrg(org_num);
                    if (p.getSpecies() == 1)
                    {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "blue", "black");
                    }
                    if (p.getSpecies() == 2)
                    {
                        if (p.getEvol() == 1)
                        {
                            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "black");
                        }
                        else
                        {
                            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "red", "black");
                        }
                    }
                }
                else
                {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                }
                org_num++;
            }
        }

        world.moveOrg();
        world.Update();
    }
};

AEAnimate animator;

int main()
{
    // Have animator call DoFrame once to start
    animator.Step();
    // animator.DoFrame();
}