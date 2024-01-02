package day12;

import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.Scanner; // Import the Scanner class to read text files
import java.util.*; 

class Day12 {


    int[][] generateHeightmap(String filename) {
        int[][] map;
        try {
            File file = new File(filename);
            Scanner scn = new Scanner(file);
            int width = 0;
            int height = 0;
            while (scn.hasNextLine()) {
                width = scn.nextLine().length();
                height++;
            }

            //init map
            map = new int[height][width];
            scn.close();
            scn = new Scanner(file);
            int i = 0;
            while (scn.hasNextLine()) {
                line = scn.nextLine();
                for (int j = 0; j < line.length(); j++) {
                    map[j][i] = line.charAt(j) - 'a' + 1;
                }
            }

            scn.close();

        } catch (FileNotFoundException e) {
            System.out.println(e);
        }

        return map;

    }



    public static void main(String[] args) {
        Day12 da = new Day12();
        int[][] map = da.generateHeightmap("test.txt");
        for (int[] v : map) {
            pritn(Arrays.toString(v));
        }

    }
}