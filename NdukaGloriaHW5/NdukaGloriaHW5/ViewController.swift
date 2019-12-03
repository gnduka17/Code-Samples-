//
//  ViewController.swift
//  NdukaGloriaHW5
//
//  Created by Gloria Nduka on 10/17/19.
//  Copyright © 2019 Gloria Nduka. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    //singleton
    var model = FlashcardsModel.shared
    let color1 = UIColor(red: 20.0/255.0, green: 13.0/255.0, blue: 242.0/255.0, alpha: 1.0)
    let color2 = UIColor(red: 245.0/255.0, green: 49.0/255.0, blue: 245.0/255.0, alpha: 1.0)
    
    @IBOutlet weak var singleTapOut: UITapGestureRecognizer!
    
    @IBOutlet weak var swipeRightOut: UISwipeGestureRecognizer!
    
    @IBOutlet weak var doubleTapOut: UITapGestureRecognizer!
    @IBOutlet weak var labelScreen: UILabel!
    
    @IBOutlet weak var swipeLeftOut: UISwipeGestureRecognizer!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        if let firstFlash = model.randomFlashcard(){
            labelScreen.text = firstFlash.getQuestion()
            labelScreen.textColor = color1
            model.questionDisplayed = true
        }else{
            labelScreen.text = ""
        }
        singleTapOut.require(toFail: doubleTapOut)
    }
    func moveAwayfromUp() {
        labelScreen.transform = CGAffineTransform(translationX: 0, y: -view.frame.size.height)
    }
    
    func moveUp(position: UIViewAnimatingPosition) {
        if let randcard = model.randomFlashcard(){
            labelScreen.text = randcard.getQuestion()
            labelScreen.textColor = color1
            model.questionDisplayed = true
        }else{
            labelScreen.text = ""
        }
        labelScreen.transform = CGAffineTransform(translationX: 0, y: view.frame.size.height)
        let backAnimator = UIViewPropertyAnimator(duration: 1, curve: .linear, animations: {() in self.labelScreen.transform = CGAffineTransform(translationX: 0, y: 0) })
        backAnimator.startAnimation()
    }
    
    @IBAction func singleTapRandomCard(_ sender: UITapGestureRecognizer) {
        let firstAnimator = UIViewPropertyAnimator (duration: 1, curve: .linear, animations: moveAwayfromUp)
        firstAnimator.addCompletion(moveUp)
        firstAnimator.startAnimation()
    }
    func fadeOutLabel() {
        labelScreen.alpha = 0
    }
    func fadeInLabel() {
        labelScreen.alpha = 1
    }
    func changeLabel(){
        if model.questionDisplayed {
            if let anscard = model.currentFlashcard() {
                model.questionDisplayed = false
                labelScreen.text = anscard.getAnswer()
                labelScreen.textColor = color2
            }else{
                labelScreen.text = ""
            }
        }else{
            if let quescard = model.currentFlashcard() {
                model.questionDisplayed = true
                labelScreen.text = quescard.getQuestion()
                labelScreen.textColor = color1
            }else{
                labelScreen.text = ""
            }
        }
    }
    
    @IBAction func doubleTapAnsQues(_ sender: UITapGestureRecognizer) {
        
        let firstAnimator = UIViewPropertyAnimator (duration: 1, curve: .linear, animations: fadeOutLabel)
        firstAnimator.addCompletion { (position) in
            self.changeLabel()
            let animator = UIViewPropertyAnimator(duration: 1,
                                                  curve: UIView.AnimationCurve.linear, animations: {() in
                                                    self.fadeInLabel()
            })
            animator.startAnimation()
        }
        firstAnimator.startAnimation()
    }
    
    func moveAwayfromRight() {
        labelScreen.transform = CGAffineTransform(translationX: view.frame.size.width, y: 0)
    }
    
    func moveRight(position: UIViewAnimatingPosition) {
        
        if let prevcard = model.previousFlashcard() {
            model.questionDisplayed = true
            labelScreen.text = prevcard.getQuestion()
            labelScreen.textColor = color1
        }else{
            labelScreen.text = ""
        }
        labelScreen.transform = CGAffineTransform(translationX: -view.frame.size.width, y: 0)
        let backAnimator = UIViewPropertyAnimator(duration: 1, curve: .linear, animations: {() in
            self.labelScreen.transform = CGAffineTransform(translationX: 0, y: 0) })
        backAnimator.startAnimation()
    }
    
    func moveAwayfromLeft() {
        labelScreen.transform = CGAffineTransform(translationX: -view.frame.size.width, y: 0)
    }
    
    func moveLeft(position: UIViewAnimatingPosition) {
        if let nextcard = model.nextFlashcard() {
            model.questionDisplayed = true
            labelScreen.text = nextcard.getQuestion()
            labelScreen.textColor = color1
        }else{
            labelScreen.text = ""
        }
        labelScreen.transform = CGAffineTransform(translationX: view.frame.size.width, y: 0)
        let backAnimator = UIViewPropertyAnimator(duration: 1, curve: .linear, animations: {() in
            self.labelScreen.transform = CGAffineTransform(translationX: 0, y: 0) })
        backAnimator.startAnimation()
    }
    
    @IBAction func swipeRight(_ sender: UISwipeGestureRecognizer) {
        let swipeAnimator = UIViewPropertyAnimator(duration: 1, curve: .linear, animations:moveAwayfromRight)
        swipeAnimator.addCompletion(moveRight)
        swipeAnimator.startAnimation()
    }
    
    @IBAction func swipeLeft(_ sender: UISwipeGestureRecognizer) {
        let swipeAnimator = UIViewPropertyAnimator(duration: 1, curve: .linear, animations:moveAwayfromLeft)
        swipeAnimator.addCompletion(moveLeft)
        swipeAnimator.startAnimation()
    }

}

