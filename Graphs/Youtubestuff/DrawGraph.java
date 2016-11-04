 
import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class DrawGraph extends JPanel
{
	public int [][] inputTable =new int[][]
			{ 	{0,1,1,1,1} ,
				{1,0,5,0,0} ,
				{1,5,0,0,1} ,
				{1,0,0,0,1} ,
				{1,0,1,1,0} ,
			};
	public String[] Nodename = new String[]{"A","B","C","D","E"};
	
	ArrayList<Node> all;
	ArrayList<Edge> edges;
	
	public void GenerateGraph()
	{
		int n= 12;
		inputTable = new int[n][n];
		Nodename = new String[n];
		for(int i=0;i< Nodename.length;i++)
		{ 
			for(int j=i+1;j< Nodename.length;j++)
			{ 
				if(Math.random() > 0.6)
				{
					inputTable[i][j] = (int)(Math.random() * 20);
					inputTable[j][i] =inputTable[i][j] ;
				}
			}
		}
		for(int i=0;i< Nodename.length;i++)
		{ 
			Nodename[i]= "" + (char)(65+i);
		}
	}
	
	public void GenerateGraph2()
	{
		int n= 12;
		inputTable = new int[n][n];
		Nodename = new String[n];
		for(int i=0;i< Nodename.length;i++)
		{ 
			for(int j=i+1;j< Nodename.length;j++)
			{ 
				if(     Math.random()/Math.log(j-i)*Math.log(2)*2 > 0.5)
				{
					inputTable[i][j] = (int)(Math.random() * 7*(j-i));
					inputTable[j][i] =inputTable[i][j] ;
				}
			}
		}
		for(int i=0;i< Nodename.length;i++)
		{ 
			Nodename[i]= "" + (char)(65+i);
		}
	}
	
	
	public void ProcessInput()
	{
		GenerateGraph();
		//GenerateGraph2();
		all = new ArrayList<Node>();
		edges =new ArrayList<Edge>();
		
		for(int i=0;i< Nodename.length;i++)
		{
			all.add(new Node());
			all.get(i).name = Nodename[i]; 
			all.get(i).Adj= new ArrayList<Edge>();
		}
		
		for(int i=0;i< Nodename.length;i++)
		{ 
			for(int j=i+1;j< Nodename.length;j++)
			{ 
				if(inputTable[i][j] != 0)
				{
					Edge e = new Edge();
					e.a = all.get(i);
					e.b = all.get(j);
					e.length = inputTable[i][j] ;
					edges.add(e);
					all.get(i).Adj.add(e);
					all.get(j).Adj.add(e); 
				}
			}
		}
	}
	
	
	
	public DrawGraph()
	{
		ProcessInput();
		Thread t = new Thread(new Runnable()
		{ 
			@Override
			public void run()
			{
				 while(true)
				 {
					try
					{
						Thread.sleep(50);
					} catch (InterruptedException e)
					{ 
						e.printStackTrace();
					}
					for(int j=0;j< Nodename.length;j++)
					{ 
						all.get(j).acc=new Vector();
						all.get(j).calForce(all);
						all.get(j). calForceEdge( ); 
						all.get(j).move();
					}
					//scale
					Scale();
					//centroid
					Vector centoid = all.get(0).getCentroid(all);
					Vector temp = (new Vector(300,300)).sub(centoid);
					for(int j=0;j< Nodename.length;j++)
					{ 
						 all.get(j).posTodraw=all.get(j).posTodraw.add(temp) ;
					}
					
					
					
					
					repaint();
					
				 }
			}
		});
		t.start();
		
		
		
		JFrame f = new JFrame();
		f.add(this);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setSize(600,600);
		f.setVisible(true);
	}

	public void paint(Graphics g)
	{
		super.paint(g);
		for(int j=0;j< Nodename.length;j++)
		{
			all.get(j).Draw(g);
		}
		for(int j=0;j< edges.size();j++)
		{
			edges.get(j).Draw(g);
		}
	}
	public static void main(String[] args)
	{
		new DrawGraph();
	}
	
	
	public void Scale()
	{
		double XMin= Integer.MAX_VALUE;
		double YMin= Integer.MAX_VALUE;
		double XMax= Integer.MIN_VALUE;
		double YMax= Integer.MIN_VALUE;
		
		for(int j=0;j< Nodename.length;j++)
		{
			if(all.get(j).pos.getX() < XMin)
			{
				XMin=all.get(j).pos.getX();
			}
			if(all.get(j).pos.getY() < YMin)
			{
				YMin=all.get(j).pos.getY();
			}
			if(all.get(j).pos.getX() > XMax)
			{
				XMax=all.get(j).pos.getX();
			}
			if(all.get(j).pos.getY() > YMax)
			{
				YMax=all.get(j).pos.getY();
			}
		}
		
		double length_x = XMax- XMin;
		double length_y = YMax- YMin;
		double length  = Math.max(length_x, length_y);
		for(int j=0;j< Nodename.length;j++)
		{
			 Vector vv = all.get(j).pos;
			 vv= vv.Mul(400.0 / length);
			 all.get(j).setPosToDraw(vv);
		}
		
		
		
	}

}
