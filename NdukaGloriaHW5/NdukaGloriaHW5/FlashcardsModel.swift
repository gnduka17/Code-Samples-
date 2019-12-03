//
//  FlashcardsModel.swift
//  NdukaGloriaHW5
//
//  Created by Gloria Nduka on 10/17/19.
//  Copyright © 2019 Gloria Nduka. All rights reserved.
//

import Foundation


class FlashcardsModel: NSObject, FlashcardsDataModel{
    
    public static let shared = FlashcardsModel()
    private var flashcards:[Flashcard]
    private var currentIndex:Int?
    var questionDisplayed:Bool
    
    override init() {
        flashcards = [Flashcard]()
        questionDisplayed = true
        currentIndex = 0
        
        flashcards.append(Flashcard(question:"How many days are in a non leap year?", answer:"365", isFavorite: false))
        flashcards.append(Flashcard(question:"Hg is the chemical symbol for which element?", answer:"Mercury", isFavorite: false))
        flashcards.append(Flashcard(question:"Which is the highest waterfall in the world?", answer:"Angel Falls, Venezuela", isFavorite: false))
        flashcards.append(Flashcard(question:"What is the most commonly diagnosed cancer in men?", answer:"Prostate cancer", isFavorite: false))
        flashcards.append(Flashcard(question:"The average person does what 13 times a day?", answer:"Laughs", isFavorite: false))
        super.init()
    }
    func numberOfFlashcards() -> Int{
        return flashcards.count
    }
    
    // returns a random card from your flashcards array
    func randomFlashcard() -> Flashcard?{
        guard let currIndex = currentIndex else {
            return nil
        }
        let size = flashcards.count
        var num = Int.random(in: 0..<5)
        if size == 1{
            return flashcards[0]
        }
        else if size > 0{
            while num == currIndex {
                num = Int.random(in: 0..<5)
            }
            
        }
        if num >= 0 && num < flashcards.count{
            currentIndex = num
            return flashcards[num]
        }
        return nil
    }
    
    func flashcard(at index: Int) -> Flashcard?{
        if index >= 0 && index < flashcards.count{
            currentIndex = index
            return flashcards[index]
        }
        return nil
    }
    func nextFlashcard() -> Flashcard?{
        guard let currIndex = currentIndex else {
            return nil
        }
        if currIndex+1 >= 0 && currIndex+1 < flashcards.count{
            currentIndex = currIndex+1
            return flashcards[currIndex+1]
        }
        else if currIndex+1 == flashcards.count {
            currentIndex = 0
            return flashcards[0]
        }
        return nil
    }
    
    func previousFlashcard() -> Flashcard?{
        guard let currIndex = currentIndex else {
            return nil
        }
        if currIndex-1 >= 0 && currIndex-1 < flashcards.count{
            currentIndex = currIndex-1
            return flashcards[currIndex-1]
        }
        else if currIndex-1 == -1 {
            currentIndex = flashcards.count-1
            return flashcards[flashcards.count-1]
        }
        
        return nil
    }
    func insert(question: String,
                answer: String,
                favorite: Bool){
        let card = Flashcard(question:question, answer:answer, isFavorite:favorite)
        flashcards.append(card)
    }
    func insert(question: String,
                answer: String,
                favorite: Bool,
                at index: Int){
        let card = Flashcard(question:question, answer:answer, isFavorite:favorite)
        guard let currIndex = currentIndex else {
            return
        }
        if index>=0 && index<flashcards.count{
            if currIndex>=0 && currIndex<flashcards.count{
                if index <= currIndex{
                    flashcards.insert(card, at: index)
                    currentIndex = currIndex + 1
                }
                
            }
        }
    }
    func currentFlashcard() -> Flashcard?{
        guard let currIndex = currentIndex, (0..<numberOfFlashcards()).contains(currIndex) else {
            return nil
        }
        return flashcards[currIndex]
    }
    func removeFlashcard(at index: Int){
        guard let currIndex = currentIndex else {
            return
        }
        if index>=0 && index<flashcards.count{
            if currIndex>=0 && currIndex<flashcards.count{
                flashcards.remove(at: index)
                if index < currIndex {
                    if index == flashcards.count - 1{
                        currentIndex = currIndex - 1
                    }
                    else if flashcards.count>1{
                        currentIndex = currIndex - 1
                    }
                    else{
                        currentIndex = nil
                    }
                }
                else if index==currIndex {
                    if flashcards.count == 1{
                        currentIndex = nil
                    }
                }
            }
        }
   }
    func toggleFavorite(){
        guard let currIndex = currentIndex else {
            return
        }
        flashcards[currIndex].isFavorite = !flashcards[currIndex].isFavorite
    }
    func favoriteFlashcards() -> [Flashcard]{
        var flashHolder:[Flashcard] = []
        for card in flashcards {
            if card.isFavorite {
                flashHolder.append(card)
            }
        }
        return flashHolder
    }
}
