import java.io.File;
import java.util.*;

public class Day4 {
    static final int SIZE = 5;    
    final String FILEPATH = "input.txt";
    int[] balls;
    ArrayList<Card> cards;
    
    void readInput() {
        cards = new ArrayList<>();
        try {
            File file = new File(FILEPATH);
            Scanner scn = new Scanner(file);
            
            //first line of balls
            String[] strballs = scn.nextLine().split(",");
            balls = new int[strballs.length];
            for (int i = 0; i < strballs.length; i++) {
                balls[i] = Integer.parseInt(strballs[i]);
            }
            
            //keep reading cards
            while (scn.hasNextLine()) {
                scn.nextLine();
                int[][] nums = new int[SIZE][SIZE];
                for (int i = 0; i < SIZE; i++) {
                    String[] strnums = scn.nextLine().trim().replaceAll("  ", " ").split(" ");
                    //System.out.println(Arrays.toString(strnums));
                    for (int j = 0; j < SIZE; j++) {
                        nums[i][j] = Integer.parseInt(strnums[j]);
                    }
                }
                cards.add(new Card(nums));
            }
            
        } catch (Exception e) {

        }
           
    }
    
    int findFirstWinnerScore() {
        for (int i : balls) {
            for (int j = 0; j < cards.size(); j++) {
                cards.get(j).mark(i);
                if (cards.get(j).bingo()) {
                    return cards.get(j).calcScore(i);
                }
            }
        }
        return -1;
    }
    
    //does mutate cards
    int findLastWinnerScore() {
        int i = 0;
        while (cards.size() > 1) {
            for (int j = 0; j < cards.size(); j++) {
                cards.get(j).mark(balls[i]);
                if (cards.get(j).bingo()) {
                    cards.remove(j);
                    j--;
                }
            }
            i++;
        }
        
        Card lastCard = cards.get(0);
        while (!lastCard.bingo()) {
            lastCard.mark(balls[i]);            
            i++;
        }
        
        return lastCard.calcScore(balls[i-1]);
    }

    
 
    public static void main(String[] args) {
        Day4 d4 = new Day4();
        //System.out.println("Hello World");
        d4.readInput();
        System.out.println(d4.findLastWinnerScore());
        
        
//        System.out.println(Arrays.toString(d4.balls));
//        System.out.println(cards.size());
//        System.out.println(Arrays.deepToString(cards.get(0).numbers));
    }
    
}


class Card {
    int[][] numbers;
    boolean[][] marked;
    
    Card(int[][] numbers) {
        this.numbers = numbers;
        marked = new boolean[Day4.SIZE][Day4.SIZE];
    }
    
    void mark(int num) {
        for (int i = 0; i < Day4.SIZE; i++) {
            for (int j = 0; j < Day4.SIZE; j++) {
                if (numbers[i][j] == num) {
                    marked[i][j] = true;
                }
            }
        }
    }
    
    boolean bingo() {
        //check rows
        for (int i = 0; i < Day4.SIZE; i++) {
            boolean bingo = true;
            for (int j = 0; j < Day4.SIZE; j++) {
                if (!marked[i][j]) {
                    bingo = false;
                }
            }
            if (bingo) {
                return true;
            }
        }
        
        //check columns
        for (int i = 0; i < Day4.SIZE; i++) {
            boolean bingo = true;
            for (int j = 0; j < Day4.SIZE; j++) {
                if (!marked[j][i]) {
                    bingo = false;
                }
            }
            if (bingo) {
                return true;
            }
        }
        return false;
    }
    
    int calcScore(int lastnum) {
        int unmarkedtally = 0;
        
        for (int i = 0; i < Day4.SIZE; i++) {
            for (int j = 0; j < Day4.SIZE; j++) {
                if (!marked[i][j]) {
                    unmarkedtally += numbers[i][j];
                }
            }
        }
        
        return lastnum * unmarkedtally;
    }
    
   
}