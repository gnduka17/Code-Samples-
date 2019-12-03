//
//  NdukaGloriaHW5Tests.swift
//  NdukaGloriaHW5Tests
//
//  Created by Gloria Nduka on 10/17/19.
//  Copyright © 2019 Gloria Nduka. All rights reserved.
//

import XCTest
@testable import NdukaGloriaHW5

class NdukaGloriaHW5Tests: XCTestCase {
    private var tester:FlashcardsModel!

    override func setUp() {
        // Put setup code here. This method is called before the invocation of each test method in the class.
        super.setUp()
        tester = FlashcardsModel()
    }

    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
    }

    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct results.
    }
    func testSize(){
        XCTAssertEqual(tester.numberOfFlashcards(),5)
    }
    
    func testSingleton() {
        let model1 = FlashcardsModel.shared
        let model2 = FlashcardsModel.shared
        model2.insert(question:"What is my name?", answer: "Gloria", favorite: false)
        XCTAssertEqual(model1.numberOfFlashcards(), model2.numberOfFlashcards())
    }
    func testInit() {
        let model1 = FlashcardsModel()
        let model2 = FlashcardsModel()
        model2.insert(question:"What is my name?", answer: "Gloria", favorite: false)
        XCTAssertNotEqual(model1.numberOfFlashcards(), model2.numberOfFlashcards())
    }
    func testRandomCard(){
        let model1 = FlashcardsModel()
        let card1 = model1.randomFlashcard()
        let card2 = model1.randomFlashcard()
        guard let newcard1 = card1 else {
            return
        }
        guard let newcard2 = card2 else {
            return
        }
        XCTAssertNotEqual(newcard1.getQuestion(), newcard2.getQuestion())
    }
    func testFlashcard(){
        guard let model1 = tester.flashcard(at: 2) else {
            return
        }
        XCTAssertEqual(model1.getQuestion(),"Which is the highest waterfall in the world?")
    }
    func testNextFlashcard(){
        guard let model1 = tester.flashcard(at: 2) else {
            return
        }
        guard let model2 = tester.nextFlashcard() else {
            return
        }
        XCTAssertEqual(model1.getQuestion(),"Which is the highest waterfall in the world?")
        XCTAssertEqual(model2.getQuestion(),"What is the most commonly diagnosed cancer in men?")
        
    }
    func testPrevFlash(){
        guard let model1 = tester.flashcard(at: 2) else {
            return
        }
        guard let model2 = tester.previousFlashcard() else {
            return
        }
        XCTAssertEqual(model1.getQuestion(),"Which is the highest waterfall in the world?")
        XCTAssertEqual(model2.getQuestion(),"Hg is the chemical symbol for which element?")
        
    }
    func testCurrentFlash(){
        guard let model1 = tester.flashcard(at: 2) else {
            return
        }
        guard let model2 = tester.currentFlashcard() else {
            return
        }
        XCTAssertEqual(model1.getQuestion(),model2.getQuestion())
        
    }
    func testToggleFav(){
        guard let model1 = tester.currentFlashcard() else {
            return
        }
        tester.toggleFavorite()
        XCTAssertEqual(model1.isFavorite,false)
    }
    func testFavFlash(){
        
    }
    

    func testPerformanceExample() {
        // This is an example of a performance test case.
        self.measure {
            // Put the code you want to measure the time of here.
        }
    }

}
