//
//  HW5FlashcardsDataModel.swift
//  ITP342HW5
//
//  Created by Harrison Weinerman on 10/5/18.
//  Copyright © 2018 Harrison Weinerman. All rights reserved.
//

import Foundation

// protocol that checks to make sure you are naming your functions like intended
//failure to follow this protol will result in a 0
protocol FlashcardsDataModel {
    //returns the number of flashcards in your flashcards array
    func numberOfFlashcards() -> Int
    // returns a random card from your flashcards array
    func randomFlashcard() -> Flashcard?
    func flashcard(at index: Int) -> Flashcard?
    func nextFlashcard() -> Flashcard?
    func previousFlashcard() -> Flashcard?
    func insert(question: String,
                answer: String,
                favorite: Bool)
    func insert(question: String,
                answer: String,
                favorite: Bool,
                at index: Int)
    func currentFlashcard() -> Flashcard?
    func removeFlashcard(at index: Int)
    func toggleFavorite()
    func favoriteFlashcards() -> [Flashcard]
}


