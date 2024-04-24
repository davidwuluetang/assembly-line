# Assembly Line Simlulator - OOP345 Project

![assemblyline](https://github.com/davidwuluetang/assembly-line/assets/122414668/dcbbc3ed-56fd-4bf3-8749-05b24890aff8)

## Project Overview

This program simulate an assembly line that consist of a set of workstations. Each workstation hold a stock item specific to that station. A line manager move customer orders from one station to another and fill up items listed in the order. Once a order process from the first workstation to the last workstation, is either completed if all items are filled or incomplete due to lack of stock. The program will print all the completed and incomplete orders once the line manager finished processing the orders.

## Modules Breakdown

*CustomerOrder* - A object contains customer name, product name, and a list of items.

*Station* - A object represent a single station on the assembly line. Each station handles a specific item for filling customer orders.

*WorkStation* - A derived class from *Station*. Customer orders are pushed to workstation, if workstation contain item listed on order then it will fill up the order. A order will be push to next workstation if all items are filled or the station run out of stocks.
  
*LineManager* - Line manager assemble workstation in specify order and gather customer orders. It will process orders and fill up order *one item* on all workstation at a time.

*Utilities* - A helper class for string parsing and token extracting from input files.

## Program Workflow

1. Construct stations from files [Stations1.txt](https://github.com/davidwuluetang/assembly-line/blob/main/Stations1.txt) and [Stations2.txt](https://github.com/davidwuluetang/assembly-line/blob/main/Stations2.txt).
2. Display all stations info and item stock number.
3. Verify station class methods.
4. Load customer orders from file [CustomerOrders.txt](https://github.com/davidwuluetang/assembly-line/blob/main/CustomerOrders.txt)
5. Display orders.
6. Load assembly line from file [AssemblyLine.txt](https://github.com/davidwuluetang/assembly-line/blob/main/AssemblyLine.txt) to *LineManager*.
7. Display assembly line before reorder, Display assembly line after reorder.
8. Run *LineManager* until all orders processed. Display filled and unfill item in each iteration.
9. Display completed and incomplete orders, and inventory.
