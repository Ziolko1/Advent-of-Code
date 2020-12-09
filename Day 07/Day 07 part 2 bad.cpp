#include <iostream>     //std::cout

int main()
{
    int bright_red      {1},
    shiny_lime          {1},
    bright_chartreuse   {1},
    clear_blue          {1},
    dull_cyan           {1},
    posh_black          {1},
    vibrant_cyan        {1},
    light_silver        {1},
    bright_maroon       {1},
    muted_gold          {1},
    striped_chartreuse  {4*posh_black+1*vibrant_cyan+2*bright_chartreuse+1},
    posh_brown_bags     {3*dull_cyan+1},
    posh_lavender       {3*bright_red+2*shiny_lime+2*bright_chartreuse+1},
    muted_olive         {4*clear_blue+1*posh_lavender+1*posh_brown_bags+2*striped_chartreuse+1},
    bright_tomato       {3*bright_maroon+3*clear_blue+5*posh_lavender+5*shiny_lime+1},
    clear_gray          {1*bright_red+2*dull_cyan+3*bright_maroon+3*muted_gold+1},
    vibrant_bronze      {5*clear_blue+1},
    striped_fuchsia     {4*posh_lavender+5*dull_cyan+2*posh_black+2*vibrant_bronze+1},
    dark_green          {1*posh_black+3*striped_fuchsia+1},
    drab_beige          {2*dark_green+2*bright_maroon+1},
    shiny_chartreuse    {5*posh_black+1*clear_blue+1},
    bright_fuchsia      {3*shiny_chartreuse+5*vibrant_bronze+1},
    plaid_black         {5*dark_green+4*bright_fuchsia+2*shiny_lime+1},
    dotted_violet       {4*light_silver+1},
    dull_lime           {2*dotted_violet+3*vibrant_cyan+1},
    faded_maroon        {5*dull_lime+1*plaid_black+5*drab_beige+5*clear_gray+1},
    dotted_red          {5*muted_olive+1*posh_lavender+2*faded_maroon+3*bright_tomato+1},
    dark_maroon         {2*bright_tomato+2*striped_chartreuse+5*bright_maroon+1},
    mirrored_olive      {4*dull_cyan+4*posh_black+2*striped_chartreuse+1},
    striped_tan         {5*mirrored_olive+4*dark_maroon+1},
    drab_plum           {5*vibrant_bronze+1*muted_olive+1*striped_tan+1},

    shiny_gold          {1*muted_olive+5*dotted_red+1*drab_plum};

    std::cout << "Answer: " << shiny_gold;
    return 0;
}
