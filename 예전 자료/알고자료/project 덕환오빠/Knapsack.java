import java.util.Random;

//import asdf.thing;

class thing{
	public thing(int w, int p) {
		weight	= w;
		price	= p;
	}
	public int weight;
	public int price;
} // Item의 무게와 가치를 함께 담을 클래스.

public class Knapsack {
	private static int N =100; // Item 개수 입력.
	private static int W = 7000; // 담을수 있는 최대 무게 입력.
	private static int dp[][] = new int[N+1][W+1]; 
	// Reculsive Property를 적용할 2차원 배열 생성. 0행과 0열은 쓰지 않음.
	public static int Max(int a, int b) {
		if(a>=b) return a;
		else return b;
	}
	public static void OptimalKnapsack(thing list[]) {
		for(int i=1;i<=N;i++) {
			for(int j=1;j<=W;j++) {
				if(j < list[i].weight){
					dp[i][j] = dp[i-1][j];
					// Reculsive Property
				}
				else {
					dp[i][j] = Max(dp[i-1][j],dp[i-1][j-list[i].weight] + list[i].price);
					// Reculsive Property
				}
				//계속 두개중 하나로 분기를 하기 때문에 2^n의 복잡도를 가지게됨.
			}
		}
	}
	public static void print() {
		for(int i=1;i<N+1;i++) {
			for(int j=1;j<W+1;j++) {
				System.out.print(dp[i][j] + " ");
			}
			System.out.println();
		} // 제대로 들어가있는지 확인하기 위한 Code
		//제출용에선 사용 X
	}
	public static void items(thing list[]) {
		int w=W;
		// 선택된 Item이 무엇이 있는지 확인해보기 위해서 만든 Code.
		System.out.print("선택된 Items\n:");
		
		for(int i=N;i>=1;i--) {
			//System.out.println("["+(i)+"]"+"["+w+"]에 대해 보겠다.");
			if(w-list[i].weight<0) continue;
			//System.out.println("["+(i-1)+"]"+"["+w+"] = " + dp[i-1][w] + ", " + "["+(i-1)+"]"+"["+(w - list[i].weight) + "] + " + list[i].price + " = " + (dp[i-1][w-list[i].weight] + list[i].price));
			if(dp[i-1][w] < dp[i-1][w-list[i].weight] + list[i].price) {
				System.out.print(i + " ");
				w = w - list[i].weight;
			}
		}

		System.out.println();
	}
	public static void main(String args[]) {
		System.out.println("12151584 유덕환 알고리즘 프로젝트");
		thing [] list = new thing[N+1];
		
		list[1] = new thing(29,22);
		list[2] = new thing(56,89);
		list[3] = new thing(125,97);
		list[4] = new thing(43,38);
		list[5] = new thing(26,24);
		list[6] = new thing(57,50);
		list[7] = new thing(117,95);
		list[8] = new thing(65,77);
		list[9] = new thing(45,79);
		list[10] = new thing(15,27);
		list[11] = new thing(51,63);
		list[12] = new thing(37,36);
		list[13] = new thing(23,33);
		list[14] = new thing(33,27);
		list[15] = new thing(66,71);
		list[16] = new thing(68,67);
		list[17] = new thing(80,80);
		list[18] = new thing(44,61);
		list[19] = new thing(144,99);
		list[20] = new thing(38,46);
		list[21] = new thing(104,92);
		list[22] = new thing(27,26);
		list[23] = new thing(36,38);
		list[24] = new thing(58,44);
		list[25] = new thing(75,63);
		list[26] = new thing(21,20);
		list[27] = new thing(42,46);
		list[28] = new thing(81,71);
		list[29] = new thing(94,75);
		list[30] = new thing(24,17);
		list[31] = new thing(29,56);
		list[32] = new thing(30,27);
		list[33] = new thing(25,36);
		list[34] = new thing(48,54);
		list[35] = new thing(120,96);
		list[36] = new thing(34,56);
		list[37] = new thing(152,104);
		list[38] = new thing(10,11);
		list[39] = new thing(9,10);
		list[40] = new thing(48,36);
		list[41] = new thing(51,100);
		list[42] = new thing(72,53);
		list[43] = new thing(36,25);
		list[44] = new thing(55,51);
		list[45] = new thing(40,69);
		list[46] = new thing(61,45);
		list[47] = new thing(69,55);
		list[48] = new thing(32,31);
		list[49] = new thing(122,94);
		list[50] = new thing(56,57);
		list[51] = new thing(71,102);
		list[52] = new thing(80,73);
		list[53] = new thing(61,88);
		list[54] = new thing(64,50);
		list[55] = new thing(18,29);
		list[56] = new thing(58,101);
		list[57] = new thing(67,103);
		list[58] = new thing(43,40);
		list[59] = new thing(77,104);
		list[60] = new thing(34,33);
		list[61] = new thing(127,93);
		list[62] = new thing(109,95);
		list[63] = new thing(75,69);
		list[64] = new thing(66,85);
		list[65] = new thing(8,9);
		list[66] = new thing(102,104);
		list[67] = new thing(73,63);
		list[68] = new thing(25,43);
		list[69] = new thing(9,14);
		list[70] = new thing(121,94);
		list[71] = new thing(80,104);
		list[72] = new thing(19,16);
		list[73] = new thing(53,91);
		list[74] = new thing(94,64);
		list[75] = new thing(109,82);
		list[76] = new thing(10,8);
		list[77] = new thing(14,12);
		list[78] = new thing(10,9);
		list[79] = new thing(27,44);
		list[80] = new thing(88,90);
		list[81] = new thing(7,8);
		list[82] = new thing(31,57);
		list[83] = new thing(90,61);
		list[84] = new thing(7,7);
		list[85] = new thing(9,12);
		list[86] = new thing(86,77);
		list[87] = new thing(21,30);
		list[88] = new thing(137,99);
		list[89] = new thing(60,60);
		list[90] = new thing(6,8);
		list[91] = new thing(18,13);
		list[92] = new thing(55,66);
		list[93] = new thing(65,60);
		list[94] = new thing(55,73);
		list[95] = new thing(40,61);
		list[96] = new thing(79,89);
		list[97] = new thing(51,39);
		list[98] = new thing(33,39);
		list[99] = new thing(14,17);
		list[100] = new thing(45,37);
		long start =  System.nanoTime();

		OptimalKnapsack(list);

		long end = System.nanoTime();

		long elapsed = end - start;

		System.out.println("최적해 : " + dp[N][W]);
		System.out.println( "경과 시간 : " + ((double)elapsed / 1000000.0) + "ms");
		//print();
		items(list);
			
	}
}
