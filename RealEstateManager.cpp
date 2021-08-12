//------------------------------------------------------------------------
// Name:    Claire Endres-50%, Devon Lee-50%
//
// Course:  CS 1430, Section 4, Fall 2020
//
// Purpose: This program manages a list of 6 real estate listings
//          including information about the listing number, type of
//          residence, square footage, and price. The program is designed
//          such that entries can be added, deleted, sorted, and
//          selectively printed based on commands from the user.
//
// Input:   Commands to modify, sort, and print the real estate listings
//          and identifiers to determine what will be added, deleted,
//          sorted, and/or printed.
//
// Output:  Comfirmation of processing a command, warning messages if
//          commands are invalid, any printed information requested,
//          and a termination message.
//------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAXSIZE = 6; // Program can track six properties at once
const int NOT_FOUND = -1;
const int SECOND_INDEX = 1;
const int HUNDRETHS = 2;

// User-entered commands
const char ADD = 'A';
const char DELETE = 'D';
const char SORT = 'S';
const char PRINT = 'P';
const char NUMBER = 'N';
const char TYPE = 'T';
const char SIZE = 'S';
const char PRICE = 'P';
const char ALL = 'A';
const char REPORT_HIGH_LOW = 'R';

int Find(const int listings[], int numProperties, int listnum);

void Add(int listings[], string types[], int sizes[],
         float prices[], int& numProperties);
void Delete(int listings[], string types[], int sizes[],
            float prices[], int& numProperties);

void Sort(int listings[], string types[], int sizes[], float prices[],
          int numProperties);
void SortByListing(int listings[], string types[], int sizes[], 
                   float prices[], int numProperties);
void SortBySize(int listings[], string types[], int sizes[],
                float prices[], int numProperties);
void SortByPrice(int listings[], string types[], int sizes[],
                 float prices[], int numProperties);

void Print(const int listings[], const string types[], const int sizes[],
           const float prices[], int numProperties);
void PrintByListing(const int listings[], int numProperties,
                    bool match[]);
void PrintByType(const string types[], int numProperties, bool match[]);
void PrintBySize(const int sizes[], int numProperties, bool match[]);
void PrintByPrice(const float prices[], int numProperties, bool match[]);
void PrintAll(int numProperties, bool match[]);
void PrintListings(const int listings[], const string types[],
                   const int sizes[], const float prices[],
                   int numProperties, const bool match[]);

void ReportHiLoPrices(const float prices[], int numProperties);

// Auxillary swap functions for sorting alrorithm
void SwapInt(int array[], int index_1, int index_2);
void SwapFloat(float array[], int index_1, int index_2);
void SwapString(string array[], int index_1, int index_2);

int main()
{
   int listings[MAXSIZE];
   string types[MAXSIZE];
   int sizes[MAXSIZE];
   float prices[MAXSIZE];
   int numProperties = 0; // Starting number of properties in arrays
   char command;
   // To display prices in the form $X.XX when printed
   cout << fixed << showpoint << setprecision(HUNDRETHS);
   cin >> command;
   while (cin)
   {
      if (command == ADD)
         Add(listings, types, sizes, prices, numProperties);
      else if (command == DELETE)
         Delete(listings, types, sizes, prices, numProperties);
      else if (command == SORT)
         Sort(listings, types, sizes, prices, numProperties);
      else if (command == PRINT)
         Print(listings, types, sizes, prices, numProperties);
      else if (command == REPORT_HIGH_LOW)
         ReportHiLoPrices(prices, numProperties);
      else
         cout << "Bad Command!" << endl;
      cin >> command;
   }
   cout << "Normal Termination of Program 4.";
   return 0;
}


//------------------------------------------------------------------------
// Function Find is a value returning function returning
// the index of the specified listing number in the array of listings.
//
// params: (in, in, in)
//------------------------------------------------------------------------
int Find(const int listings[], int numProperties, int listingInput)
{
   for (int i = 0; i <= numProperties; i++)
      if (listings[i] == listingInput)
         return i;

   return NOT_FOUND;
}

//------------------------------------------------------------------------
// Function Add reads the data for a new listing such as listing number,
// type, size and price. It calls function find to see if the number
// is already in the listings array and displays the exists message. If
// listings array is full, it displays the full message. Otherwise, it
// will add the information to the end of the arrays and increments
// number of properties.
//
// params: (inout, inout, inout, inout, inout)
//------------------------------------------------------------------------
void Add(int listings[], string types[], int sizes[],
         float prices[], int& numProperties)
{
   int listingInput;
   string typeInput;
   int sizeInput;
   float priceInput;

   cin >> listingInput >> typeInput >> sizeInput >> priceInput;

   if (numProperties == MAXSIZE)
      cout << "#" << listingInput
           << " wasn't added. No more room." << endl;
   else if (Find(listings, numProperties, listingInput) != NOT_FOUND)
      cout << "#" << listingInput << " exists in the listings." << endl;
   else
   {
      listings[numProperties] = listingInput;
      types[numProperties] = typeInput;
      sizes[numProperties] = sizeInput;
      prices[numProperties] = priceInput;
      numProperties++;
      cout << "#" << listingInput
           << " was added to the listings." << endl;
   }

   return;
}

//------------------------------------------------------------------------
// Function Delete reads the listing number to delete. It calls function
// find to see if the number is not in the listings array and displays
// an error message. Otherwise, it deletes the listing information from
// the arrays by copying the last entry into the entry being deleted
// and decrements the number of properties.
//
// params: (inout, inout, inout, inout, inout)
//------------------------------------------------------------------------
void Delete(int listings[], string types[], int sizes[],
            float prices[], int& numProperties)
{
   int listingInput, indexToDelete;
   cin >> listingInput;

   indexToDelete = Find(listings, numProperties, listingInput);

   if (indexToDelete == NOT_FOUND)
      cout << "#" << listingInput
           << " not removed.  Doesn't exist in the listings." << endl;
   else
   {
      listings[indexToDelete] = listings[numProperties - 1];
      types[indexToDelete] = types[numProperties - 1];
      sizes[indexToDelete] = sizes[numProperties - 1];
      prices[indexToDelete] = prices[numProperties - 1];
      numProperties--;

      cout << "#" << listingInput
           << " removed from the listings." << endl;
   }

   return;
}


//------------------------------------------------------------------------
// Function Sort reads the sort type and performs a selection sort
// based on the type such as number, size or price.
//
// params: (inout, inout, inout, inout, in)
//------------------------------------------------------------------------
void Sort(int listings[], string types[], int sizes[], float prices[],
          int numProperties)
{
   char sortType;
   cin >> sortType;

   if (sortType == NUMBER)
      SortByListing(listings, types, sizes, prices, numProperties);
   if (sortType == SIZE)
      SortBySize(listings, types, sizes, prices, numProperties);
   if (sortType == PRICE)
      SortByPrice(listings, types, sizes, prices, numProperties);

   return;
}

//------------------------------------------------------------------------
// Function SortByListing reorders listings, types, sizes, and prices
// arrays based on listing number
// params: (inout , inout , inout , inout , in )
//------------------------------------------------------------------------
void SortByListing(int listings[], string types[], int sizes[],
                   float prices[], int numProperties)
{
   int minIndex;
   for (int i = 0; i < numProperties - 1; i++)
   {
      minIndex = i;
      for (int j = i + 1; j < numProperties; j++)
      {
         if (listings[j] < listings[minIndex])
            minIndex = j;
      }
      SwapInt(listings, i, minIndex);
      SwapInt(sizes, i, minIndex);
      SwapFloat(prices, i, minIndex);
      SwapString(types, i, minIndex);
   }

   cout << "Listings sorted by listing number." << endl;

   return;
}

//------------------------------------------------------------------------
// Function SortBySize reorders listings, types, sizes, and prices
// arrays based on size
// params: (inout, inout, inout, inout, in)
//------------------------------------------------------------------------
void SortBySize(int listings[], string types[], int sizes[],
                float prices[], int numProperties)
{
   int minIndex;
   for (int i = 0; i < numProperties - 1; i++)
   {
      minIndex = i;
      for (int j = i + 1; j < numProperties; j++)
      {
         if (sizes[j] < sizes[minIndex])
            minIndex = j;
      }
      SwapInt(listings, i, minIndex);
      SwapInt(sizes, i, minIndex);
      SwapFloat(prices, i, minIndex);
      SwapString(types, i, minIndex);
   }

   cout << "Listings sorted by size." << endl;

   return;
}

//------------------------------------------------------------------------
// Function SortByPrice reorders listings, types, sizes, and prices
// arrays based on price
// params: (inout, inout, inout, inout, in)
//-----------------------------------------------------------------------
void SortByPrice(int listings[], string types[], int sizes[],
                 float prices[], int numProperties)
{
   int minIndex;
   for (int i = 0; i < numProperties - 1; i++)
   {
      minIndex = i;
      for (int j = i + 1; j < numProperties; j++)
      {
         if (prices[j] < prices[minIndex])
            minIndex = j;
      }
      SwapInt(listings, i, minIndex);
      SwapInt(sizes, i, minIndex);
      SwapFloat(prices, i, minIndex);
      SwapString(types, i, minIndex);
   }

   cout << "Listings sorted by price." << endl;

   return;
}


//------------------------------------------------------------------------
// Function Print displays the listings to match the type of print being
// generated. It uses the inputted data to choose through the listings
// to be printed.  The Listing types are number, type, size and price.
//
// params: (in, in, in, in, in)
//------------------------------------------------------------------------
void Print(const int listings[], const string types[], const int sizes[],
           const float prices[], int numProperties)
{
   // Array to track which properties meet the specifications for printing
   bool match[MAXSIZE];
   char printType;

   cin >> printType;

   if (printType == NUMBER)
      PrintByListing(listings, numProperties, match);
   if (printType == TYPE)
      PrintByType(types, numProperties, match);
   if (printType == SIZE)
      PrintBySize(sizes, numProperties, match);
   if (printType == PRICE)
      PrintByPrice(prices, numProperties, match);
   if (printType == ALL)
      PrintAll(numProperties, match);

   PrintListings(listings, types, sizes, prices, numProperties, match);

   return;
}

//------------------------------------------------------------------------
// Function PrintByListing searches through the listing array for a
// match to the specified listing and sets the index of the boolean
// array corresponding to the index of the listing array that match
// the specified listing.
//
// params: (in, in, inout)
//------------------------------------------------------------------------
void PrintByListing(const int listings[], int numProperties, bool match[])
{
   int currListing;
   cin >> currListing;
   for (int i = 0; i < numProperties; i++)
   {
      // Sets boolean array to determine which element will be printed
      if (listings[i] == currListing)
         match[i] = true;
      else
         match[i] = false;
   }

   cout << "Printing the listing #" << currListing << ":" << endl;

   return;
}

//------------------------------------------------------------------------
// Function PrintByType searches through the type array for
// matches to the specified type and sets the indices of the boolean
// array corresponding to the indices of the type array that match
// the specified type.
//
// params: (in, in, inout)
//------------------------------------------------------------------------
void PrintByType(const string types[], int numProperties, bool match[])
{
   string currType;
   cin >> currType;
   for (int i = 0; i < numProperties; i++)
   {
      // Sets boolean array to determine which elements will be printed
      if (types[i] == currType)
         match[i] = true;
      else
         match[i] = false;
   }

   cout << "Printing the listings of type " << currType << ":" << endl;

   return;
}

//------------------------------------------------------------------------
// Function PrintBySize searches through the size array for
// matches to the specified size and sets the indices of the boolean
// array corresponding to the indices of the size array that match
// the specified size.
//
// params: (in, in, inout)
//------------------------------------------------------------------------
void PrintBySize(const int sizes[], int numProperties, bool match[])
{
   int currSize;
   cin >> currSize;
   for (int i = 0; i < numProperties; i++)
   {
      // Sets boolean array to determine which elements will be printed
      if (sizes[i] == currSize)
         match[i] = true;
      else
         match[i] = false;
   }

   cout << "Printing the listings of size "
        << currSize << " sqft:" << endl;

   return;
}

//------------------------------------------------------------------------
// Function PrintByPrice searches through the price array for
// matches to the specified price and sets the indices of the boolean
// array corresponding to the indices of the price array that match
// the specified price.
//
// params: (in, in, inout)
//------------------------------------------------------------------------
void PrintByPrice(const float prices[], int numProperties, bool match[])
{
   float currPrice;
   cin >> currPrice;
   for (int i = 0; i < numProperties; i++)
   {
      // Sets boolean array to determine which elements will be printed
      if (prices[i] == currPrice)
         match[i] = true;
      else
         match[i] = false;
   }

   cout << "Printing the listings of price $" << currPrice << ":";
   cout << endl;

   return;
}

//------------------------------------------------------------------------
// Function PrintAll sets all values of the boolean array to "true" so
// that every entry will be printed.
//
// params: (in, in)
//------------------------------------------------------------------------
void PrintAll(int numProperties, bool match[])
{
   for (int i = 0; i < numProperties; i++)
      match[i] = true;

   cout << "Printing All the listings:" << endl;

   return;
}

//------------------------------------------------------------------------
// Function PrintListings searches through the match array for "true"
// values and prints the corresponding index of each array holding
// information about the property.
//
// params: (in, in, in)
//------------------------------------------------------------------------
void PrintListings(const int listings[], const string types[],
   const int sizes[], const float prices[],
   int numProperties, const bool match[])
{
   for (int i = 0; i < numProperties; i++)
      if (match[i] == true)
         cout << listings[i] << " " << types[i] << " "
         << prices[i] << " " << sizes[i] << endl;

   return;
}

//------------------------------------------------------------------------
// Function ReportHiLoPrices determines the highest and lowest price
// in the prices array and displays these values.
//
// params: (in, in)
//------------------------------------------------------------------------
void ReportHiLoPrices(const float prices[], int numProperties)
{
   if (numProperties > 1)
   {
      float minPrice = prices[0];
      float maxPrice = prices[0];

      for (int i = SECOND_INDEX; i < numProperties; i++)
      {
         // Resets max/min price if the current index is the new min/max
         if (prices[i] > maxPrice)
            maxPrice = prices[i];
         if (prices[i] < minPrice)
            minPrice = prices[i];
      }

      cout << "Highest price = " << maxPrice
           << " Lowest price = " << minPrice << endl;
   }

   return;
}


//------------------------------------------------------------------------
// Function SwapInt swaps the values in two specified index positions of
// an array of integers
//
// params: (inout, in, in)
//------------------------------------------------------------------------
void SwapInt(int array[], int index_1, int index_2)
{
   int value_1 = array[index_1];
   int value_2 = array[index_2];
   array[index_1] = value_2;
   array[index_2] = value_1;
   return;
}

//------------------------------------------------------------------------
// Function SwapFloat swaps the values in two specified index positions
// of an array of floats
//
// params: (inout, in, in)
//------------------------------------------------------------------------
void SwapFloat(float array[], int index_1, int index_2)
{
   float value_1 = array[index_1];
   float value_2 = array[index_2];
   array[index_1] = value_2;
   array[index_2] = value_1;
   return;
}

//------------------------------------------------------------------------
// Function SwapString swaps the values in two specified index positions
// of an array of strings
//
// params: (inout, in, in)
//------------------------------------------------------------------------
void SwapString(string array[], int index_1, int index_2)
{
   string value_1 = array[index_1];
   string value_2 = array[index_2];
   array[index_1] = value_2;
   array[index_2] = value_1;
   return;
}
