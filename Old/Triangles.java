import java.util.*;
import java.io.*;

public class Triangles {
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new FileReader("triangles.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("triangles.out")));
		
		int n = Integer.parseInt(br.readLine());
		int[] xs = new int[n];
		int[] ys = new int[n];
		for (int i = 0; i <= n-1; i++) {
			String[] split = br.readLine().split(" ");
			xs[i] = Integer.parseInt(split[0]);
		        ys[i] = Integer.parseInt(split[1]);
		}

		int maxDoubleArea = 0;
		for(int i = 0; i <= n-1; i++) {
			for(int j = i+1; j <= n-1; j++) {
				for(int k = j+1; k <= n-1; k++) {
					// check if the points make a triangle
					// find area
					boolean verticalSide = xs[i] == xs[j] || xs[i] == xs[k] || xs[j] == xs[k];
					boolean horizontalSide = ys[i] == ys[j] || ys[i] == ys[k] || ys[j] == ys[k];
					if(verticalSide && horizontalSide) {
						int xLeg = Math.max(Math.abs(xs[j]-xs[i]), Math.abs(xs[k]-xs[i]));
						int yLeg = Math.max(Math.abs(ys[j]-ys[i]), Math.abs(ys[k]-ys[i]));
						maxDoubleArea = Math.max(maxDoubleArea, xLeg * yLeg);
					}
				}
			}
		}

		pw.print(maxDoubleArea);
		
		br.close(); pw.close();
	}
}