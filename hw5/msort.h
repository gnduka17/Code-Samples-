#ifndef MSORT_H
#define MSORT_H
#include <iostream>
#include <vector>


template <class T, class Comparator>
void merge(std::vector<T>& myArray, std::vector<T>& left, std::vector<T>& right, Comparator comp){
	int a =0;
	int i =0;
	int j = 0;
	for(i; i<left.size();i++){
		for(j; right.size();j++){
			if(comp(left[i], right[j])){
				myArray[a] =right[j];
				continue;
			}
			else{
				myArray[a]=left[i];
				i++;
			}
			a++;
		}
	}
	while(i<left.size()){
		myArray[a]=left[i];
		i++;
		a++;
	}
	while(j<right.size()){
		myArray[a]=right[j];
		j++;
		a++;
	}	
}

template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, Comparator comp){
	int size=myArray.size();

	if(myArray.size()<2){
		return;
	}

	int mid =myArray.size()/2;

	std::vector<T>leftside(mid);

	std::vector<T> rightside(myArray.size()-mid);

	for(int i =0; i<=mid-1;i++){
		leftside[i] = myArray[i];
	}

	for(int j=mid;j<=myArray.size()-1;j++){
		rightside[j-mid]=myArray[j];
	}

	mergeSort(leftside, comp);
	mergeSort(rightside, comp);
	merge(myArray, leftside, rightside, comp);
	mergeSort(myArray, comp);
}

#endif