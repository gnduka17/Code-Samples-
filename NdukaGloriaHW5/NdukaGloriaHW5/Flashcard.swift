//
//  Flashcard.swift
//  NdukaGloriaHW5
//
//  Created by Gloria Nduka on 10/17/19.
//  Copyright © 2019 Gloria Nduka. All rights reserved.
//

import Foundation

struct Flashcard:Equatable{
    private var question:String
    private var answer:String
    public var isFavorite:Bool
    func getQuestion()->String{
        return question
    }
    func getAnswer()->String{
        return answer
    }
    init(question: String, answer: String, isFavorite: Bool=false){
        self.question = question
        self.answer = answer
        self.isFavorite = isFavorite
    }
}
