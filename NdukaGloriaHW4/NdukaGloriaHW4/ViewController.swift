//
//  ViewController.swift
//  NdukaGloriaHW4
//
//  Created by Gloria Nduka on 10/6/19.
//  Copyright © 2019 Gloria Nduka. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet weak var inputNum: UITextField!
    @IBOutlet weak var tipSliderValueLabel: UILabel!
    @IBOutlet weak var taxSC: UISegmentedControl!
    //@IBOutlet weak var outputLabel: UILabel!
    @IBOutlet weak var viewDisplay: UIView!
    
    @IBOutlet weak var sliderVar: UISlider!
    @IBOutlet weak var switchVar: UISwitch!
    @IBOutlet weak var splitStepperValueLabel: UILabel!
    @IBOutlet weak var taxLabel: UILabel!
    @IBOutlet weak var subtotalLabel: UILabel!
    @IBOutlet weak var tipAmountLabel: UILabel!
    
    @IBOutlet weak var totalwTipLabel: UILabel!
    
    @IBOutlet weak var totalPerPersonLabel: UILabel!
    
    @IBOutlet weak var stepperObj: UIStepper!
    
    @IBOutlet weak var clearButton: UIButton!
    
    @IBOutlet weak var taxLabelChange: UILabel!
    
    @IBOutlet weak var totalWTipLabelChange: UILabel!
    
    @IBOutlet weak var tipLabelChange: UILabel!
    @IBOutlet weak var subTLabelChange: UILabel!
    
    @IBOutlet weak var totalPerPersLabelChange: UILabel!
    
    @IBOutlet weak var billLabel: UILabel!
    
    @IBOutlet weak var taxSegLabel: UILabel!
    
    @IBOutlet weak var includeTaxLabel: UILabel!
    
    @IBOutlet weak var splitLabelword: UILabel!
    
    @IBOutlet weak var tipCalcLabell: UILabel!
    
    var billAmount:Double = 0.0
    var taxPercent:Double = 0.0
    var taxAmount:Double = 0.0
    var subtotal:Double = 0.0
    var tipVal:Double = 0.0
    var totalnTip:Double = 0.0
    var tipPercent:Double = 0.0
    var totalSplit:Double = 0.0
    var splitNum:Int = 1
    var taxFlag:Bool = false
    
    
    func setAccessibilityIdentifiers() {
        //set up all the identfiers
        
        //ui components you can interact with
        inputNum.accessibilityIdentifier = HW4AccessibilityIdentifiers.billTextField
        taxSC.accessibilityIdentifier = HW4AccessibilityIdentifiers.segmentedTax
        switchVar.accessibilityIdentifier = HW4AccessibilityIdentifiers.includeTaxSwitch
        sliderVar.accessibilityIdentifier = HW4AccessibilityIdentifiers.tipSlider
        stepperObj.accessibilityIdentifier = HW4AccessibilityIdentifiers.splitStepper
        clearButton.accessibilityIdentifier = HW4AccessibilityIdentifiers.resetButton
        //dyanmic labels that will change based on userinput
        
        taxLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.taxAmountLabel
        subtotalLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.subtotalAmountLabel
        tipAmountLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.tipAmountLabel
        totalwTipLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.totalWithTipAmountLabel
        totalPerPersonLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.totalPerPersonAmountLabel
        tipSliderValueLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.sliderLabel
        splitStepperValueLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.splitLabel
        //static labels that dont change - title labels
        
        tipCalcLabell.accessibilityIdentifier = HW4AccessibilityIdentifiers.tipCalculaterLabel
        billLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.billLabel
        taxSegLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.segmentedLabel
        includeTaxLabel.accessibilityIdentifier = HW4AccessibilityIdentifiers.includeTaxLabel
        splitLabelword.accessibilityIdentifier = HW4AccessibilityIdentifiers.evenSplitLabel
        taxLabelChange.accessibilityIdentifier = HW4AccessibilityIdentifiers.taxLabel
        subTLabelChange.accessibilityIdentifier = HW4AccessibilityIdentifiers.subtotalLabel
        tipLabelChange.accessibilityIdentifier = HW4AccessibilityIdentifiers.tipLabel
        totalWTipLabelChange.accessibilityIdentifier = HW4AccessibilityIdentifiers.totalWithTipLabel
        totalPerPersLabelChange.accessibilityIdentifier = HW4AccessibilityIdentifiers.totalPerPersonLabel
        //user view; only need to connect one
        
        viewDisplay.accessibilityIdentifier = HW4AccessibilityIdentifiers.view
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        setDefaultValues()
        setAccessibilityIdentifiers()
    }
    @IBAction func keyboardLeaveBackgroundTap(_ sender: UITapGestureRecognizer) {
        updateUI()
        inputNum.resignFirstResponder()
    }
    
    @IBAction func segmentedNums(_ sender: UISegmentedControl) {
            let num = sender.titleForSegment(at: sender.selectedSegmentIndex) ?? ""
            taxPercent = Double(num) ?? 0.0
            taxPercent = taxPercent/100.0
            updateUI()
    }
    @IBAction func taxSwitch(_ sender: UISwitch) {
        let switchtax = sender.isOn
        taxFlag = switchtax
        updateUI()
    }
    @IBAction func tipSlide(_ sender: UISlider) {
        let num = Int(sender.value.rounded())
        tipSliderValueLabel.text = "\(num)%"
        tipPercent = Double(num)
        tipPercent = tipPercent/100.0
        updateUI()
    }
    @IBAction func splitStep(_ sender: UIStepper) {
        let num = sender.value
        splitStepperValueLabel.text="\(Int(num))"
        splitNum = Int(num)
        updateUI()
    }
    @IBAction func buttonTapped(_ sender: UIButton) {
        let alert = UIAlertController(title: "Clear All Values?", message: "Are you sure you want to clear all values?", preferredStyle: .actionSheet)
        
        let cancelAction = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
        alert.addAction(cancelAction)
        
        let clearAction = UIAlertAction(title: "Clear All", style: .destructive, handler: clearButtonTapped)
        alert.addAction(clearAction)
        
        present(alert, animated: true)

    }
    func clearButtonTapped(action: UIAlertAction) {
        clearAll()
    }
    private func updateUI(){
        let billA = inputNum.text ?? ""
        billAmount = Double(billA) ?? 0.0
        taxAmount = billAmount * taxPercent
        taxLabel.text = String(format:"$%.2f",taxAmount)
        if taxFlag == true {
            subtotal = billAmount + taxAmount
        }
        else{
            subtotal = billAmount
        }
        subtotalLabel.text = String(format:"$%.2f",subtotal)
        tipVal = subtotal * tipPercent
        tipAmountLabel.text = String(format:"$%.2f",tipVal)
        totalnTip = billAmount + tipVal + taxAmount
        totalwTipLabel.text = String(format:"$%.2f",totalnTip)
        if splitNum == 0{
            totalSplit = totalnTip
        }
        else{
            totalSplit = totalnTip / Double(splitNum)
        }
        
        totalPerPersonLabel.text = String(format:"$%.2f",totalSplit)
    }
    private func clearAll(){
        setDefaultValues()
    }
    private func setDefaultValues(){
        billAmount = 0.0
        taxPercent = 0.0
        taxAmount = 0.0
        subtotal = 0.0
        tipVal = 0.0
        totalnTip = 0.0
        tipPercent = 0.0
        totalSplit = 0.0
        splitNum  = 1
        taxFlag = false
        tipSliderValueLabel.text = "\(0)%"
        sliderVar.value = 0
        splitStepperValueLabel.text="\(1)"
        switchVar.setOn(false, animated:true)
        inputNum.text=""
        taxSC.selectedSegmentIndex = 0
        totalPerPersonLabel.text = String(format:"$%.2f",billAmount)
        totalwTipLabel.text = String(format:"$%.2f",billAmount)
        tipAmountLabel.text = String(format:"$%.2f", billAmount)
        subtotalLabel.text = String(format:"$%.2f",billAmount)
        taxLabel.text = String(format:"$%.2f",billAmount)
    }
}
