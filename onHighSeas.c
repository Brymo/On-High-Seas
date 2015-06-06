#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>


#define NUMOFFSET 49

#define TRUE 1
#define FALSE 0

//Color Code taken from stackoverflow.com, by Andrejs Cainikovs.

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define DOCTOR 49
#define GUARD 50
#define MUSO 51
#define NAVIG 52
#define FISHER 53


typedef struct _seadog{


   char* name;
   int hunger;
   int skill;
   int wounded;
   int alive;


}seadog;


typedef struct _seaDogDetails{

   int career;
   int ID;

}seaDogDetails;

typedef struct _seafood{

   char*type;
   int foodVal;

}seafood;


typedef struct _crew{

   seadog team[5][3];

   int useful[5];

   int morale;
   int food;
   int dubloons;

   int maxActions;
   int actionsLeft;

   int seals;

   int buoy;
   int kittens;

   int gg;



}crew;

typedef struct _crew * Crew;

void crewInitialise(Crew c);
void initialiseNames(Crew c);
void initialiseStats(Crew c);
void initialiseBoat(Crew c);

void allocName(Crew c, int career, int ID,char * name);
void allocStats(Crew c, int career);

void soItBegins(Crew c);
void useSeals(Crew c);

int actionCost(Crew c, int career);

int goodGetChar();

void speak(Crew c);
void talkSpecific(Crew c, int input);
void talkTeam(Crew c, int input);
void activeSkills(Crew c, int career);
void actOnInput(Crew c, int userInput);

void healAll(Crew c);
void hitSomething(Crew c);
void playTune(Crew c);
char * songRand();
void scan(Crew c);
void strayKitten(Crew c);
void fish(Crew c);


void skillMsg(Crew c, int career, int alive);
void personalInterface(Crew c, int career, int person);
void multiFeed(Crew c, int career);
void feed(Crew c, int career, int person);
void sail(Crew c);
void grub(Crew c);
void eat(Crew c);
void isHungry(Crew c, int career, int teamID);
void howHungry(int hunger, char * name);
void postFeed(int hunger, char * name);
void isStarved(Crew c, int careerCount,int teamCount);
void misery(Crew c);
void howMiserable(Crew c,int morale);
void buoyPass(Crew c);
void randEvents(Crew c, int selection);
void nickWight(Crew c);
void merchantShip(Crew c);
void CapnKitty(Crew c);
void raidingParty(Crew c);
void stolen(Crew c, int loss);

void viewWound(Crew c);
void viewHunger(Crew c);

void richBucksChest(Crew c);
void openChest(Crew c);
void jakeBoom(Crew c);
void kitty(Crew c);
void lotsADubloons(Crew c);
void feast(Crew c);
void sealOfKanhere(Crew c);

void wounding(Crew c, int career, int ID);

void allFree (Crew c);
int timeRand(int max);
char * banf();
int getAliveInTeam(Crew c, int input);
int getAliveInCrew(Crew c);
void dubDeduct(Crew c, int career);

seaDogDetails getValidNPC(Crew c);
seaDogDetails getDeadNPC(Crew c);

int main(int argc, char * argv[]){

   printf(CYAN);

   printf("............................\n");

   printf("Welcome to the High Seas!\n");

   Crew c = malloc(sizeof(crew));

   printf("don't let your crew get hungry.\n");

   crewInitialise(c);

   printf("Remember to keep morale up too!\n");

   printf("Pick a number to begin!\n");

   printf(RESET);

   soItBegins(c);

   printf("Thank you for playing!");

   allFree(c);


return EXIT_SUCCESS;

}


void soItBegins(Crew c){


   while(c->gg == FALSE){

      printf(BLUE"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


      printf(RESET"Buoys passed: %d\n", c->buoy);
      printf(MAGENTA"Kittens: %d\n"RESET, c->kittens);
      printf(YELLOW"Dubloons: %d\n"RESET, c->dubloons);
      printf(GREEN"Food: %d\n"RESET, c->food);
      printf(CYAN"Morale: %d\n"RESET, c->morale);

      printf(BLUE"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"RESET);

      printf("Please choose an action ");
      printf(RED"(Actions Left: %d)\n"RESET, c->actionsLeft);

      printf("1)Sail\n");
      printf("2)Use a seal of Kanhere(Seals:%d)\n", c->seals);

      printf("3)View Wounded\n");
      printf("4)View hunger\n");

      printf("5)Heal all wounds(-%d actions)\n", actionCost(c, 0));
      printf("6)Revive a random member(-%d actions)\n", actionCost(c, 1));
      printf("7)Play a song(-%d actions)\n", actionCost(c, 2));
      printf("8)Scan the sea(-%d actions)\n", actionCost(c, 3));
      printf("9)Fish for food(-%d actions)\n", actionCost(c, 4));


      int input = goodGetChar();


      if (input == '1'){

         sail(c);


      }else if (input == '2'){

         useSeals(c);

      }else if (input == '3'){

         viewWound(c);

      }else if (input == '4'){

         viewHunger(c);

      }else if (input >= '5' && input <= '9'){

         actOnInput(c, input);

      }


   }

}

void actOnInput(Crew c, int userInput){

   int career = '9'-userInput;

   if(c->actionsLeft >= actionCost(c, career)){

      if (career == 0){

         fish(c);

      }else if (career == 1){

         scan(c);

      }else if (career == 2){

         playTune(c);

      }else if (career == 3){

         hitSomething(c);

      }else if (career == 4){

         healAll(c);

      }

      c->actionsLeft -= actionCost(c, career);

   }else{

      printf(MAGENTA"You've run out of actions!\n");
      printf("Sail again to get actions.\n"RESET);

   }



}

void viewWound(Crew c){

   seaDogDetails NPC = getValidNPC(c);

   char * NPCname  = c->team[NPC.career][NPC.ID].name;

   int career = 0;
   int ID = 0;
   int isThereWounded = FALSE;

   printf("%s:Here's a list of all injured as requested Cap'n.\n", NPCname);

   while(career <= 4){

         while(ID <= 2){

               if(c->team[career][ID].wounded == TRUE){

                  isThereWounded = TRUE;
                  printf(YELLOW"%s\n"RESET,c->team[career][ID].name );

               }

            ID++;

         }

         //printf("Career: %d, ID: %d\n", career, ID);
         ID = 0;
         career++;

      }

      if(isThereWounded == FALSE){

         printf("%s:ARRR! There be no-one on the list!\n", NPCname);

      }


}

void viewHunger(Crew c){

   seaDogDetails NPC = getValidNPC(c);

   char * NPCname  = c->team[NPC.career][NPC.ID].name;

   int career = 0;
   int ID = 0;

   printf("%s:Here's a list of how hungry we are Cap'n.\n", NPCname);

   while(career <= 4){

         while(ID <= 2){

            if(c->team[career][ID].hunger > 50){

               printf(YELLOW);

            }else{

               printf(RED);

            }

            printf("%s:%d/100\n",c->team[career][ID].name,c->team[career][ID].hunger);

            printf(RESET);

            ID++;

         }

         //printf("Career: %d, ID: %d\n", career, ID);
         ID = 0;
         career++;

      }



}

int actionCost(Crew c, int career){

   int baseCost = 4-c->useful[career];

   if(baseCost == 4){

      baseCost = 999;

   }

   return baseCost;

}

void useSeals(Crew c){

   if(c->seals > 0){

      printf("You break open one of the seals.\n");
      printf(GREEN"Max actions per turn +1\n");
      printf("Actions restored to full!\n"RESET);

      c->maxActions++;
      c->actionsLeft = c->maxActions;

   }else{

      printf("You have no seals!\n");

   }


}

int goodGetChar(){

   int charInput = getchar();

      if(charInput == 10){

         charInput = getchar();

      }

   return charInput;

}

void sail(Crew c){

   int randInput = timeRand(20);

   eat(c);

   grub(c);

   misery(c);

   c->buoy += (c->useful[3]*10)+(c->kittens);

   randEvents(c, randInput);

   c->actionsLeft = c->maxActions;

}

void eat(Crew c){


   int career =  0;
   int ID = 0;
   int lowestHunger = 100;
   //int dogCount = 0;
   //int firstTime = FALSE;
   int currentLow = 0;

   seaDogDetails lowest;
   lowest.career = 0;
   lowest.ID = 0;

   while(currentLow <= 75 && c->food > 0){

      lowestHunger = 100;

      while(career <= 4){

         while(ID <= 2){

            if(c->team[career][ID].hunger <= lowestHunger){

               lowestHunger = c->team[career][ID].hunger;
               currentLow = lowestHunger;
               lowest.career = career;
               lowest.ID = ID;

            }

            ID++;

         }

         //printf("Career: %d, ID: %d\n", career, ID);
         ID = 0;
         career++;

      }

      if(career >= 5){

         career = 4;

      }

      if(career >= 3){

         career = 2;

      }


      if(c->food > 0 && lowestHunger <= 75){

         printf("%s ate some food.\n",c->team[lowest.career][lowest.ID].name );

         feed(c, lowest.career, lowest.ID);


      }

      ID = 0;
      career = 0;
      lowest.ID = 0;
      lowest.career = 0;


   }

}

void randEvents(Crew c, int selection){

   int aliveTest = getAliveInCrew(c);


   if(selection == 0){

      if(aliveTest != 15){

         nickWight(c);

      }else{

         printf("A cold wind blows...\n");

      }

   }else if(selection == 1){

      merchantShip(c);

   }else if(selection == 2){

      CapnKitty(c);

   }else if(selection >= 3 && selection <= 5){

      raidingParty(c);

   }else{

      //calmSeas();

   }

}

void nickWight(Crew c){

   seaDogDetails NPC1 = getValidNPC(c);
   seaDogDetails NPC2 = getValidNPC(c);

   int crewDead = 15 - getAliveInCrew(c);

   int foodStolen = (c->food/15) * (crewDead);
   int goldGone = (c->dubloons/15) * (crewDead);
   int moraleDown = (c->morale/15) * (crewDead);

   printf("A terrifying chill fills the air...\n");
   printf("%s: This is...\n", c->team[NPC1.career][NPC1.ID].name);
   printf("%s: NICKING WIGHTS!  EVERYONE HIDE!\n",c->team[NPC2.career][NPC2.ID].name);

   printf("Screeching fills the air; suddenly subsiding into\n");
   printf("the hollow crash of the surrounding waves.\n");

   printf("Upon inspecting the storeroom, %s finds\n", c->team[NPC2.career][NPC2.ID].name);
   printf("%d food has been stolen, along with %d dubloons!\n", foodStolen, goldGone);

   printf("Suffering from shock, ship morale has decreased by %d!\n", moraleDown);

   c->food -= foodStolen;
   c->dubloons -= goldGone;
   c->morale -= moraleDown;

}

void merchantShip(Crew c){

  printf(MAGENTA);
  seaDogDetails NPC1 = getValidNPC(c);
  int cost = (timeRand(10)+1)*10;
  int input = 0;
  int toBuy = 0;

  printf("%s:Cap'n, we've signalled in a nearby merchant ship!\n", c->team[NPC1.career][NPC1.ID].name);

  printf(GREEN"Dubloons Left: %d\n"RESET, c->dubloons);

  printf("Merchant: Welcome to my store! Please buy some food!\n");
  printf("Merchant: My prices are %d dubloons a piece.\n", cost);

  printf("1)Buy food\n");
  printf("2)Leave store\n");

  input = goodGetChar();

  if (input == '1'){

     printf("Please enter how much food you want to buy:");
     scanf("%d", &toBuy);

     if(c->dubloons >= toBuy*cost){

        printf("Merchant: That'll be %d dubloons!\n", toBuy*cost);

        c->dubloons -= toBuy*cost;
        c->food += toBuy;
        printf(GREEN"Dubloons Left: %d\n"GREEN, c->dubloons);

        printf("Merchant: Thank You!  Come Again!\n");
        printf("You return to the high seas.\n");

     }else{

        printf("Merchant: Do you take me for a fool?\n");
        printf("Merchant: You lack the coin for this purchase!\n");

        printf(RED"The merchant kicks you out.\n"RESET);

     }



  }else{

     printf("You thank the merchant and return to the high seas.\n");

  }

  printf(RESET);

}

void CapnKitty(Crew c){

  printf(MAGENTA);

  seaDogDetails NPC1 = getValidNPC(c);
  int cost = (timeRand(5)+1)*100;
  int input = 0;
  int toBuy = 0;

  printf("%s:Cap'n, we've spotted Cap'n Kitty's Crew!\n", c->team[NPC1.career][NPC1.ID].name);

  printf(GREEN"Dubloons Left: %d\n"RESET, c->dubloons);

  printf(MAGENTA"Kitty: *Meow* Welcome to my ship! Please buy my kittens!\n");
  printf("Kitty: My prices are %d dubloons a cat.\n", cost);

  printf("1)Buy kitten\n");
  printf("2)Part ways\n");

  input = goodGetChar();

  if (input == '1'){

     printf("*Meow* How many kittens d'ya want?:");
     scanf("%d", &toBuy);

     if(c->dubloons >= toBuy*cost){

        printf("Kitty: That'll be %d dubloons!\n", toBuy*cost);

        c->dubloons -= toBuy*cost;
        c->kittens += toBuy;
        printf(GREEN"Dubloons Left: %d\n"RESET, c->dubloons);

        printf(MAGENTA"Kitty: Cya next time!\n");
        printf("You return to the high seas.\n");

     }else{

        printf("Kitty: Pssh, ya dun have enough dubloons.\n");
        printf("Kitty: Tryin to cheat me again?\n");

        printf(RED"Captain Kitty kicks you off her ship.\n"RESET);

     }



  }else{

     printf("You:So long Kitty...*meow?*\n");

  }

  printf(RESET);

}

void raidingParty(Crew c){


   int guardsLeft = c->useful[1];
   seaDogDetails NPC = getValidNPC(c);
   char * NPCname = c->team[NPC.career][NPC.ID].name;

   int goldLoss = (3-guardsLeft)*200;
   int gains = (timeRand(6)+1)*100;

   printf(YELLOW);

   printf("%s: Cap'n, Jake Boom's raiders are attacking our ship!\n",  NPCname);

   if(guardsLeft == 0){

       printf("%s: We've been overwhelmed!\n",NPCname);
       printf("%s: I'm sorry captain...\n",NPCname);
       printf(RED "%s is shot by a Boom raider.\n" RESET,NPCname);

       printf("Raider: KEKEKEKEKEKK!!!\n");
       printf(RED "The raiders escape with %d in stolen dubloons.\n" RESET, goldLoss);

       c->team[NPC.career][NPC.ID].alive = FALSE;
       c->useful[NPC.career]--;

       stolen(c, goldLoss);


   }else if(guardsLeft == 1){

       printf("Guard: Don't worry!  I got this!\n");
       printf("%s: There's too many of them!\n",  c->team[NPC.career][NPC.ID].name);
       printf("%s: Goodbye captain...\n",NPCname);
       printf(RED "%s is shot by a Boom raider.\n" RESET,NPCname);

       printf("Raider: LOL!\n");
       printf(RED"The raiders escape with %d in stolen dubloons.\n"RESET, goldLoss);

       c->team[NPC.career][NPC.ID].alive = FALSE;
       c->useful[NPC.career]--;

       stolen(c, goldLoss);

   }else if(guardsLeft == 2){

       printf("Guards: WE FIGHT!\n");
       printf("After a valiant fight, the raiders are warded off\n");
       printf(RED"%s is left wounded, %d was stolen"RESET, NPCname, goldLoss);

       c->team[NPC.career][NPC.ID].wounded = TRUE;
       c->useful[NPC.career]--;

       stolen(c, goldLoss);

   }else if(guardsLeft == 3){

       printf("Guards: FOR THE CAPTAIN!!!\n");
       printf("You guards brutally massacre the intruders.\n");
       printf(GREEN"%d dubloons are looted off their bodies!\n"RESET, gains);

       c->dubloons += gains;

   }


}

void stolen(Crew c, int loss){

   c->dubloons -= loss;

   if(c->dubloons < 0){

      c->dubloons = 0;

   }

   printf(YELLOW"Dubloons Left: %d\n"RESET, c->dubloons);

}

void richBucksChest(Crew c){

   printf(CYAN"You found one of Richbuck's random chests!\n");
   printf("Who knows what the legendary pirate has stored inside...\n"RESET);

   printf("1)Open Chest\n");
   printf("2)Feed it to the sea\n");

   int chestInput = goodGetChar();

   if(chestInput == '1'){

      openChest(c);

   }else if (chestInput == '2'){

      printf("You threw the chest back into the ocean.\n");

   }else{

      printf("Please enter a valid number\n");
   }



}

void openChest(Crew c){

   printf("You gingerly pry open the chest...\n");

   int randomInt = timeRand(5);

   if(randomInt == 0){

      jakeBoom(c);

   }else if(randomInt == 1){

      kitty(c);

   }else if(randomInt == 2){

      lotsADubloons(c);

   }else if(randomInt == 3){

      feast(c);

   }else if(randomInt == 4){

      sealOfKanhere(c);

   }


}

void jakeBoom(Crew c){

   printf("A scrawny lad dressed in dynamite rolls out of\n");
   printf("the chest.\n");

   printf("Boom Mnion: 'FOR JAKE BOOM!!! DIE!!!\n");


   int randomInt = timeRand(2);

   if(randomInt == 0){

      printf("The Boom Minion explodes violently.\n");

      int careerRand = rand()%5;

      int IDRand = rand()%3;

      wounding(c, careerRand,IDRand);

      printf(RED"The resulting shockwave wounds %s\n"RESET,c->team[careerRand][IDRand].name);

   }else{

      int goldRand = 100 + rand()%3;

      printf(GREEN"Jake Boom explodes into a shower of %d dubloons\n"RESET, goldRand);

      c->dubloons += goldRand;

   }

}


void kitty(Crew c){

   int kitCount = timeRand(3)+2;

   printf("%d kittens roll out of the box...\n", kitCount);
   printf("1)Keep them\n");
   printf("2)Turn them into food\n");

   int catInput = goodGetChar();

   if (catInput == '1'){

      printf(MAGENTA"You welcome the kittens to the ship!\n"RESET);
      c->kittens++;

   }else if (catInput == 2){

     printf("You cry a little and kill the kittens.\n");
     printf(GREEN"+%d food\n"RESET, kitCount*2);

     c->food += kitCount*2;

   }

}

void lotsADubloons(Crew c){

   seaDogDetails healthy = getValidNPC(c);

   int randCoins = 500+timeRand(5)*300;

   printf("A fountain of dubloons eject from the chest.\n");
   printf("%s counts %d dubloons in profit.", c->team[healthy.career][healthy.ID].name,randCoins);

   c->dubloons += randCoins;

   printf(GREEN"Dubloons Left: %d\n"RESET, c->dubloons);


}

void feast(Crew c){

   printf("A conveyor belt rolls out of the chest, with\n");
   printf("numerous plates of sushi soon emeging.");

   printf(GREEN"Everyone's hunger is restored a little"RESET);

   int career = 0;

   int ID = 0;

   while(career <= 4){

      while(ID <= 2){

         c->team[career][ID].hunger += 50;

            if(c->team[career][ID].hunger > 100){

               c->team[career][ID].hunger = 100;

            }

         ID++;

      }
      career++;

   }

}

void sealOfKanhere(Crew c){

   printf("From the chest, endian voice whispers,\n");
   printf("sending a chill down your spine.\n");

   int coinToss = timeRand(2);

   if (coinToss == 0){

      c->seals++;

      printf("Kanhere...approves.\n");
      printf("The dust in the chest hardens into a seal of Kanhere.\n");
      printf("You currently have %d seals\n", c->seals);



   }else{

      seaDogDetails healthy = getValidNPC(c);

      printf("Kanhere...DOES NOT APPROVE!\n");
      printf("The whiper turns into an agonising screech,\n");
      printf("crippling %s\n", c->team[healthy.career][healthy.ID].name);

      wounding(c, healthy.career, healthy.ID);

   }

}



seaDogDetails getValidNPC(Crew c){

   int randomCareer = timeRand(5);

   int randomID = timeRand(3);

   int deathCount = 0;

   seaDogDetails validDog;

   seadog curDog = c->team[randomCareer][randomID];

   while(curDog.alive == FALSE && curDog.wounded == FALSE){

      deathCount++;

      randomID = (randomID + 1)%3;

      if (deathCount == 3){

         randomCareer = (randomCareer + 1)%5;

         deathCount = 0;

      }

      curDog = c->team[randomCareer][randomID];


   }

   validDog.career = randomCareer;
   validDog.ID = randomID;

   return validDog;

}

seaDogDetails getDeadNPC(Crew c){

   int randomCareer = timeRand(5);

   int randomID = timeRand(3);

   int aliveCount = 0;

   seaDogDetails validDog;

   seadog curDog = c->team[randomCareer][randomID];

   while(curDog.alive == TRUE){

      aliveCount++;

      randomID = (randomID + 1)%3;

      if (aliveCount == 3){

         randomCareer = (randomCareer + 1)%5;

         aliveCount = 0;

      }

      curDog = c->team[randomCareer][randomID];


   }

   validDog.career = randomCareer;
   validDog.ID = randomID;

   return validDog;

}



void grub(Crew c){


   int careerCount = 0;
   int teamCount = 0;

   int lastTime = time(NULL);

   int hungerDeduct = 0;

   srand(lastTime);

   while (careerCount <= 4){

      while (teamCount <= 2){

         if(c->team[careerCount][teamCount].alive==TRUE){

            hungerDeduct = 3*((rand()%4)+1);

            c->team[careerCount][teamCount].hunger -= hungerDeduct;

            isStarved(c,careerCount,teamCount);

            if(c->team[careerCount][teamCount].alive==TRUE){

               isHungry(c,careerCount,teamCount);

               lastTime = lastTime*(lastTime-1);

               srand(lastTime);

            }

         }

         teamCount++;

      }

      teamCount = 0;

      careerCount++;

   }



}

void isStarved(Crew c, int careerCount,int teamCount){

   if(c->team[careerCount][teamCount].hunger<=0){

      c->team[careerCount][teamCount].alive=FALSE;
      c->useful[careerCount]--;
      c->morale -= 10;

      howMiserable(c,c->morale);

      printf(RED "%s has starved to death\n",c->team[careerCount][teamCount].name);

      printf(RESET);

   }

}

void isHungry(Crew c, int career, int teamID){


   int hunger = c->team[career][teamID].hunger;
   char * name = c->team[career][teamID].name;


      printf(YELLOW);
      howHungry(hunger,name);
      printf(RESET);


}

void howHungry(int hunger, char * name){

   if(hunger < 100/4){

      printf("%s is REALLY hungry!\n",name);

   }else if(hunger < 100/3){

      printf("%s is really hungry!\n",name);

   }else if(hunger < 100/2){

      printf("%s is hungry.\n",name);

   }

}

void misery(Crew c){

   c->morale -= (5-c->useful[2])*2;

   howMiserable(c,c->morale);


}

void howMiserable(Crew c, int morale){


   if(morale <= 0){

      printf(RED"You're crew has mutinied!\n");
      printf("Game Over\n"RESET);

      c->gg = TRUE;


   }else if(morale < 10){

      printf("You're crew is enraged!\n");

   }else if(morale < 30){

      printf("Your crew is annoyed...\n");

   }else if(morale < 50){

      printf("Your crew is agitated...\n");

   }else if(morale < 70){

      printf("Your crew is not amused.\n");

   }else if(morale < 90){

      printf("Your crew is content.\n");

   }else if(morale <= 100){

      printf("Your crew is jolly!\n");

   }

}

void buoyPass(Crew c){

   c->buoy += (c->useful[3]*10)+(c->kittens);
   printf(RESET"Buoys passed: %d \n"RESET, c->buoy);

}

void speak(Crew c){

   printf("Which team would you like to speak to?\n");
   printf("1) Doctors\n");
   printf("2) Guards\n");
   printf("3) Musicians\n");
   printf("4) Navigators\n");
   printf("5) Fisherman\n");

   int career = goodGetChar();


   if (career <= '5' && career >= '1'){

      talkTeam(c,career);

   }else{

      printf("Please enter a valid number");

   }



}

void talkTeam(Crew c, int input){


   int alive = getAliveInTeam(c, input);
   int career = input - NUMOFFSET;
   int userInput;

   int cost = 800 - (c->useful[career]*200);

   printf("What should this team do?\n");
   printf("1) Eat (- %d food)\n", alive);

   printf("2)");

   skillMsg(c,career, alive);

   userInput = goodGetChar();
   //printf("TEST HERE: %d", userInput);


   if(userInput == '1'){

      if(c->food >= alive){

         multiFeed(c, career);

      }else{

         printf(RED"Not enough food!\n"RESET);

      }


   }else if (userInput == '2'){



      if(c->dubloons >= cost){

         activeSkills(c, career);

      }else{

         printf("Not enough dubloons!\n");

      }

   }


}

void activeSkills(Crew c, int skill){



   if (skill == 0){

      healAll(c);

   }else if (skill == 1){

      hitSomething(c);

   }else if (skill == 2){

      playTune(c);

   }else if (skill == 3){

      scan(c);

   }else if (skill == 4){

      fish(c);

   }

}

void healAll(Crew c){

   int career = 0;
   int ID = 0;

   printf(GREEN"Your doctors heal everyone's wounds!\n"RESET);

   while(career <= 4){

      while(ID <= 2){

         if(c->team[career][ID].wounded == TRUE){

             c->team[career][ID].wounded = FALSE;
             c->useful[career]++;

         }

         ID++;

      }

      career++;
   }


}

void hitSomething(Crew c){

   int coinFlip = timeRand(2);
   int career = 0;
   int allAlive = TRUE;

   seaDogDetails deadDog;

   if (coinFlip == 0){

      while(career <= 4){

         if(c->useful[career] != 3){

            allAlive = FALSE;

         }

         career++;

      }

      if(allAlive == FALSE){

         deadDog = getDeadNPC(c);

         printf(GREEN"The guards punched the corpse of \n");
         printf("%s so hard that death got knocked\n", c->team[deadDog.career][deadDog.ID].name);
         printf("out of it, bringing the pirate back to life!\n"RESET);



         c->team[deadDog.career][deadDog.ID].alive = TRUE;
         c->useful[career]++;



      }else{

         printf(GREEN"There was no one to revive.\n"RESET);

      }


   }else{

   }

}

void playTune(Crew c){

   char * songChoice = songRand();

   if(c->morale < 100){

      c->morale += 30;

      if(c->morale > 100){

         c->morale = 100;

      }


      printf(GREEN"The musician play %s.\n", songChoice);
      printf("Everyone feels better.\n"RESET);

      free(songChoice);



   }else{

      printf(GREEN"The crew's morale couldn't be any better!\n"RESET);

   }


}

char * songRand(){


   char * songs[5];
   int i = 0;

   while (i < 5){

      songs[i] = malloc(sizeof(char)*20);

      i++;

   }


   strcpy(songs[0], "Call Me Maybe");
   strcpy(songs[1], "The ballad of Salil");
   strcpy(songs[2], "The duck song");
   strcpy(songs[3], "Pachelbel canon in d");
   strcpy(songs[4], "something awesome");

   int choice = timeRand(5);

   i=0;


   while (i < 5){

      if(i != choice){

         free(songs[i]);

      }

      i++;

   }


   return songs[choice];

}

void scan(Crew c){

  int thingSeen = timeRand(3);

  if(thingSeen == 0){

     richBucksChest(c);

  }else if(thingSeen == 1){

     strayKitten(c);

  }else if(thingSeen == 2){

     printf(GREEN"The navigators see...a lot of water...\n"RESET);

  }

}

void strayKitten(Crew c){

   printf(CYAN"You navigators spot a kitten floating\n");
   printf(" buoys behind the ship.\n");
   printf("Sail back to rescue it?\n"RESET);

   printf("1) Yes\n");
   printf("2) No\n");

   int input = goodGetChar();

   if(input == '1'){

      printf(GREEN"You welcome the kitten to the crew!"RESET);
      c->buoy -= 90;
      printf(BLUE"Buoys passed: %d"RESET, c->buoy);
      c->kittens++;

   }else{

      printf(GREEN"You leave the kitten behind.\n"RESET);

   }

}

void fish(Crew c){

   seafood fishType[5];
   int randFish = timeRand(5);

   int i = 0;


   while(i < 5){

      fishType[i].type = malloc(sizeof(char)*10);
      i++;

   }

   strcpy(fishType[0].type, "Shrimp");
   fishType[0].foodVal = 1;

   strcpy(fishType[1].type, "Big Shrimp");
   fishType[1].foodVal = 2;

   strcpy(fishType[2].type, "Mega Shrimp");
   fishType[2].foodVal = 3;

   strcpy(fishType[3].type, "Lord Shrimp");
   fishType[3].foodVal = 4;

   strcpy(fishType[4].type, "Shimpzilla");
   fishType[4].foodVal = 5;

   printf(GREEN"The fishermen caught a %s, adding %d food\n",fishType[randFish].type,fishType[randFish].foodVal );
   printf("to the food stores!\n"RESET);

   c->food += fishType[randFish].foodVal;

   printf(GREEN"Food Left: %d \n"RESET, c->food);

   i = 0;

   while(i < 5){

      free(fishType[i].type);

      i++;

   }

}



void skillMsg(Crew c, int career, int alive){

   int cost = 800 - ((c->useful[career]*100)*2);

   if (career == 0){

      printf("Heal all wounded (- %d dubloons)\n", cost);
      printf("'Heals wounds of all pirates on ship'");

   }else if(career == 1){

      printf("Revive(- %d dubloons)\n", cost);
      printf("'Bring a random dead pirate back to life'\n");

   }else if(career == 2){

      printf("Play a song (- %d dubloons)\n", cost);
      printf("Boost morale of ship\n");

   }else if(career == 3){

      printf("Scan the sea (- %d dubloons)\n", cost);
      printf("'Chance to find treasure'\n");

   }else if(career == 4){

      printf("Go fish (- %d dubloons)\n", cost);
      printf("'Chance to find find food'\n");

   }

}

int getAliveInCrew(Crew c){

   int i = 49;
   int living = 0;

   while(i < 54){

      living += getAliveInTeam(c, i);

      i++;

   }

   return living;

}

int getAliveInTeam(Crew c, int input){

   int career = input - NUMOFFSET;

   int ID = 0;
   int alive = 0;

   while (ID <= 2){

      if(c->team[career][ID].alive == TRUE){

         alive++;

      }

      ID++;

   }

   return alive;

}

void talkSpecific(Crew c, int input){

   int count = 0;

   int career = input - NUMOFFSET;

   printf("Who in this team would you like to speak to?\n");

   while (count <= 2){

      printf("%d) %s\n", (count+1), c->team[career][count].name);

      count++;

   }

   int person = goodGetChar();

   personalInterface(c, career, person);

}

void personalInterface(Crew c, int career, int person){

   printf("1) Give food\n");

   int input = goodGetChar();

   int personID = person - NUMOFFSET;

   if (input == '1'){

      feed(c, career, personID);

   }
}

void multiFeed(Crew c, int career){

   int ID = 0;

   printf("Fed all members in this team!\n");
   printf("Food left: %d", c->food);

   while(ID <= 2){

      feed(c, career, ID);

      ID++;

   }

   printf("Food left: %d\n", c->food);

}

void feed(Crew c, int career, int person){

   c->food--;

   c->team[career][person].hunger += 25;

   if (c->team[career][person].hunger > 100){

      c->team[career][person].hunger = 100;

   }

   //postFeed(c->team[career][person].hunger, c->team[career][person].name);

}


void postFeed(int hunger, char * name){

   printf(YELLOW);

   if(hunger < 100/4){

      printf("%s is still REALLY hungry!\n",name);

   }else if(hunger < 100/3){

      printf("%s is still really hungry!\n",name);

   }else if(hunger < 100/2){

      printf("%s is still hungry.\n",name);

   }else if(hunger == 100){

      printf("%s is full!\n",name);

   }else{

      printf("%s is content.\n", name);

   }

   printf(RESET);

}

void allFree (Crew c){

   int career = 1;
   int teamID = 0;

   while (career <= 4){

      while(teamID <= 2){

         free(c->team[career][teamID].name);

         teamID++;

      }

      teamID = 0;
      career++;

   }

   free(c);

}

void crewInitialise(Crew c){

   initialiseNames(c);

   initialiseStats(c);

   initialiseBoat(c);


}

void initialiseNames(Crew c){

   allocName(c,0,0,"Doctor Mannan");
   allocName(c,0,1,"Doctor Corey");
   allocName(c,0,2,"Doctor Charly");

   allocName(c,1,0,"Guard Joerick");
   allocName(c,1,1,"Guard Mitsuaki");
   allocName(c,1,2,"Guard Leon");

   allocName(c,2,0,"Musician Michael");
   allocName(c,2,1,"Musician Luke");
   allocName(c,2,2,"Musician Matthew");

   allocName(c,3,0,"Navigator Ajay");
   allocName(c,3,1,"Navigator Chris");
   allocName(c,3,2,"Navigator Kevin");

   allocName(c,4,0,"Fisherman Ryan");
   allocName(c,4,1,"Fisherman Meghana");
   allocName(c,4,2,"Fisherman Ilan");

   //allocName(c,6,0,"Salil");
   //allocName(c,6,1,"Richard");
   //allocName(c,6,2,"Whyte");



}

void initialiseStats(Crew c){

   int career = 0;

   while(career <= 4){

      allocStats(c,career);
      career++;

   }

}

void initialiseBoat(Crew c){

   c->food = 20;
   c->morale = 100;
   c->buoy = 0;
   c->gg = FALSE;
   c->dubloons = 500;

   c->maxActions = 3;
   c->actionsLeft = 3;

   c->seals = 0;
   c->kittens = 0;


   int count = 0;

   while(count<5){

      c->useful[count]=3;

      count++;

   }



}


void allocStats(Crew c, int career){

   int count = 0;


      while (count < 3){


         c->team[career][count].skill = 20;

         c->team[career][count].hunger = 100;

         c->team[career][count].alive = TRUE;

         c->team[career][count].wounded = FALSE;



         count++;

      }






}


void allocName(Crew c, int career, int ID,char*name){

   c->team[career][ID].name = malloc(strlen(name));

   strcpy(c->team[career][ID].name,name);

   //printf("Address %d%d:%p, Name:%s, FirstName:%s\n", career,ID,c->team[career][ID].name,c->team[career][ID].name,c->team[0][0].name);



}

int timeRand(int max){

   int randomInt = 0;

   srand(time(NULL));

   randomInt = rand()%max;

   return randomInt;

}



void wounding(Crew c, int career, int ID){

   c->team[career][ID].wounded = TRUE;
   c->useful[career]--;

}

char * banf(){

   char * store = malloc(sizeof(char)*20);

   int i = 0 ;

   char input = goodGetChar();


   while(input != '\n'){

      store[i] = input;

      input = goodGetChar();

      i++;

   }

   return store;

}
