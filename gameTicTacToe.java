// Example code from the lesson
// Improved by PetrelPine

// Java program for Tic-Tac-Toe Game

import java.util.*;

public class gameTicTacToe {
    
    static String[] board;
    static String turn;
    
    // check if the game is over and try to find the winner, return the winner status
    static String checkWinner() {
        
        // check every pattern to find the winner
        for (int a = 0; a < 8; a++) {
            String line = switch (a) {
                case 0 -> board[0] + board[1] + board[2];
                case 1 -> board[3] + board[4] + board[5];
                case 2 -> board[6] + board[7] + board[8];
                case 3 -> board[0] + board[3] + board[6];
                case 4 -> board[1] + board[4] + board[7];
                case 5 -> board[2] + board[5] + board[8];
                case 6 -> board[0] + board[4] + board[8];
                case 7 -> board[2] + board[4] + board[6];
                default -> null;
            };
            
            // if X wins
            if (line.equals("XXX")) {
                return "X";
            }
            
            // if O wins
            else if (line.equals("OOO")) {
                return "O";
            }
        }
        
        // check if draw
        for (int a = 0; a < 9; a++) {
            if (Arrays.asList(board).contains(String.valueOf(a + 1))) {
                break;
            } else if (a == 8) {
                return "draw";
            }
        }
        
        System.out.println(turn + "'s turn, please enter a slot number to place " + turn + " in: ");
        return null;  // undetermined
    }
    
    /*
    board example
    |---|---|---|
	| 1 | 2 | 3 |
	|-----------|
	| 4 | 5 | 6 |
	|-----------|
	| 7 | 8 | 9 |
	|---|---|---|
	*/
    // print out the board
    static void printBoard() {
        String[] tempBoard = board.clone();
        
        for (int i = 0; i < tempBoard.length; i++) {
            if (tempBoard[i].equals("X")) {
                tempBoard[i] = "\033[34mX\033[0m";  // blue
            } else if (board[i].equals("O")) {
                tempBoard[i] = "\033[33mO\033[0m";  // yellow
            } else {
                tempBoard[i] = String.format("\033[0m%s\033[0m", tempBoard[i]);  // default
            }
        }
        
        System.out.println("|---|---|---|");
        System.out.println("| " + tempBoard[0] + " | " + tempBoard[1] + " | " + tempBoard[2] + " |");
        System.out.println("|-----------|");
        System.out.println("| " + tempBoard[3] + " | " + tempBoard[4] + " | " + tempBoard[5] + " |");
        System.out.println("|-----------|");
        System.out.println("| " + tempBoard[6] + " | " + tempBoard[7] + " | " + tempBoard[8] + " |");
        System.out.println("|---|---|---|");
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        board = new String[9];
        turn = "X";
        String winner = null;
        
        for (int a = 0; a < 9; a++) {
            board[a] = String.valueOf(a + 1);
        }
        
        System.out.println("Welcome to 3x3 Tic Tac Toe.");
        printBoard();
        
        System.out.println("X will play first. Please enter a slot number to place X in: ");
        
        while (winner == null) {
            int numInput;
            
            // Exception handling, check the validity of numbers
            try {
                numInput = in.nextInt();
                if (!(numInput >= 1 && numInput <= 9)) {
                    System.out.println("\033[31mInvalid input, please re-enter slot number: \033[0m");  // red
                    continue;
                }
            } catch (InputMismatchException e) {
                System.out.println("\033[31mInvalid input, please re-enter slot number: \033[0m");  // red
                in.next();  // fix infinite loop bug
                continue;
            }
            
            // if the slot is not taken
            if (board[numInput - 1].equals(
                String.valueOf(numInput))) {
                board[numInput - 1] = turn;
                
                // change turn
                if (turn.equals("X")) turn = "O"; else turn = "X";
                
                printBoard();
                winner = checkWinner();
            }
            // the slot is already taken
            else {
                System.out.println("\033[31mSlot already taken, please re-enter slot number: \033[0m");  // red
            }
        }
        
        // draw
        if (winner.equalsIgnoreCase("draw")) {
            System.out.println("It's a draw! Thanks for playing.");
        }
        // has winner
        else {
            System.out.println("Congratulations, " + winner + " has won! Thanks for playing.");
        }
    }
}
