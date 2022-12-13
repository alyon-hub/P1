#include <stdio.h>
#include <stdlib.h>

//Avriel Lyon
//9/13/2021
//Smoothie Struct Assignment

//for each ingredient
typedef struct item{
	int itemID;
	int numParts;
} item;

//for each recipe
typedef struct recipe{
	int numItems;
	item * itemList;
	int totalParts;
} recipe;

//declaring functions
char ** readIngredients(int numIngredients);
recipe ** readAllRecipes(int numRecipes);
recipe * readRecipe (int numItems);
double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients);
void printOrder(char** ingredientNames, double* orderList, int numIngredients);
void freeRecipes(recipe** allRecipes, int numRecipes);
void freeIngredients(char ** ingredientList, int numIngredients);



int main(){
	int numIngredients; //number of ingredients available
	int numRecipes; // number of smoothie recipes
	int numSmoothies;
	
	int numStores; //number of stores
	char ** ingredientNames; //array for all ingredient names
	recipe ** recipeList; //recipe array for all recipes
	
	int i;
	
	scanf("%d", &numIngredients); //takes in the number of ingredients
	ingredientNames = readIngredients(numIngredients); //calls readIngredients function and returns a char array
	
	scanf("%d", &numRecipes); //takes in the number of recipes
	recipeList = readAllRecipes(numRecipes); //calls readAllRecipes function and returns recipe struct array
	
	
	
	scanf("%d", &numStores); //takes in the number of stores
	
	for(i = 0; i < numStores; i++){
		printf("Store #%d:\n" , i+1);
		scanf("%d", &numSmoothies); //takes in the number of smoothies a store makes

		double* orderList = calculateOrder(numSmoothies, recipeList, numIngredients); //calculate order list
	    printOrder(ingredientNames, orderList, numIngredients); //print out the order
	}
	
	freeRecipes(recipeList,numRecipes); //free recipe memory
	freeIngredients(ingredientNames, numIngredients); //free ingredient names memory
	
	return 0;
}


//reads in the ingredient names and creates a string array
char ** readIngredients(int numIngredients){
	char ** ingredientNames = malloc((numIngredients * 100) * sizeof(char));
	int i;
	
	for(i = 0; i < numIngredients; i++){
		ingredientNames[i] = malloc(100 * sizeof(char));
		scanf("%s", ingredientNames[i]);	
	}
	
	//returns string array
	return ingredientNames;
}

//calls readRecipe and creates an array pointing to each recipe struct
recipe ** readAllRecipes(int numRecipes){
	struct recipe** smoothieList;
	smoothieList = (struct recipe**)malloc(numRecipes * sizeof(recipe *));
	int i;
	int numItems;
	
	//readRecipe -> struct, smoothieList -> array of readRecipe structs
	for(i = 0; i < numRecipes; i++){

		scanf("%d", &numItems);
		smoothieList[i] = readRecipe(numItems);
		
	}
	
	//returns list of multiple structs
	return smoothieList;
}

//makes a single recipe struct
recipe * readRecipe (int numItems){
	//declaring a struct and allocating space for it
	struct recipe * recipeList = (struct recipe*)malloc(sizeof(recipe));
	int i;
	int totalParts = 0;
	
	//Allocate space in the itemList array in the recipe struct
	recipeList->itemList = malloc(numItems * sizeof(recipe));
	recipeList->numItems = numItems;
	
	for (i = 0; i < numItems; i++){
		//sets the values in the itemList struct array
		scanf("%d", &recipeList->itemList[i].itemID);
	    scanf("%d", &recipeList->itemList[i].numParts);
	    
	    //calculates the total parts
	    totalParts += recipeList->itemList[i].numParts;
	    recipeList->totalParts = totalParts;
	}	
	
	//returns struct
	return recipeList;
}

//calculates the weight of each ingredient in the specified smoothie recipe
double * calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients){
	int i;
	int recipeNum;
	double recipeWeight;
	//setting each iteration in amtOfEachItem to zero in case an ingredient is not used
	//then later to print, ignore zeroes in the order
	double * amtOfEachItem = calloc(numSmoothies * numIngredients , sizeof(double));
	double numParts = 0;
	double totalParts = 0;
	int j;
	
	for (i = 0; i < numSmoothies; i++){
		
		//get the number of the recipe to know where to look
		scanf("%d", &recipeNum);
		//get the weight amount that the store sells of that recipe
		scanf("%lf", &recipeWeight);
		
		//variable to store total parts 
		totalParts = (*recipeList[recipeNum]).totalParts;
		
		//variable for numItems
		int loop = recipeList[recipeNum]->numItems;
		
		for(j = 0; j < loop ; j++){
			//for each point in amtOfEachItem that corresponds with the itemID,
			//calculate the amount of ingredient needed
			int itemID = recipeList[recipeNum]->itemList[j].itemID;
			numParts = recipeList[recipeNum]->itemList[j].numParts;
			amtOfEachItem[itemID] += (double)(recipeWeight/totalParts) * numParts;
		}
			
	 }
	
	//returns array containing each amount of each ingredient that is needed
    return amtOfEachItem;
}

//prints out the order
void printOrder(char** ingredientNames, double* orderList, int numIngredients){
	int i;
	
	for(i = 0; i < numIngredients; i++){
		//if there is no amount of the ingredient, then print
		if( orderList[i] != 0){
			printf("%s " , ingredientNames[i]);
			printf("%.6lf\n", orderList[i]);
		}
	}
	
}


void freeRecipes(recipe** allRecipes, int numRecipes){
	int i;
	
	//free each recipe at index i
	for(i = 0; i < numRecipes; i++){
		free(allRecipes[i]);
	}
	
	//free anything left over
	free(allRecipes);
}

void freeIngredients(char ** ingredientList, int numIngredients){
	int i;
	
	//free each ingredient at index i
	for(i = 0; i < numIngredients; i++){
		free(ingredientList[i]);
	}
	
	//free anything left over
	free(ingredientList);
}


