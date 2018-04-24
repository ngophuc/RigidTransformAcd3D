# RigidTransformAcd3D

To install the program see <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/INSTALL.txt">INSTALL.txt</a> file


If you want you can also directly test the programm online:

http://ipol-geometry.loria.fr/~phuc/ipol_demo/DecompConvexRigidMotion/


* [![Build Status](https://travis-ci.org/ngophuc/RigidTransformAcd3D.svg?branch=master)](https://travis-ci.org/ngophuc/RigidTransformAcd3D)

# Program parameters

Allowed options are: 
<table align="right">
  <tr>
    <th>-h [ --help ]</th>
    <th>display this message.</th>
  </tr>
  <tr>
    <td>-i [ --input ] arg</td>
    <td>input filename. <br></td>
  </tr>
  <tr>
    <td>-o [ --output ] arg (=./) </td>
    <td>output dir (default ./).</td>
  </tr>
</table>

  -d [ --dir ] arg (=./)                execute dir (default ./).<br>
  -x [ --tx ] arg (=0)                  x-translation.<br>
  -y [ --ty ] arg (=0)                  y-translation.<br>
  -z [ --tz ] arg (=0)                  y-translation.<br>
  -a [ --alpha ] arg (=0)               rotation angle by x-axis.<br>
  -b [ --beta ] arg (=0)                rotation angle by y-axis.<br>
  -g [ --gamma ] arg (=0)               rotation angle by z-axis.<br>
  -s [ --scale ] arg (=100)          	scale data.<br>
  -r [ --resolution ] arg (=100000)     decomposition parameter resolution.<br>
  --depth arg (=20)                     decomposition parameter depth.<br>
  -m [ --minVolumePerCH ] arg (=0.0001) decomposition parameter minVolumePerCH.<br>

# Examples

<p>File <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/flower.pgm">flower.pgm</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./transformDecomShape3d -i ../Samples/egea.obj -o ../Results/egea_res.obj --resolution 1000000 --depth 30 --minVolumePerCH 0.0
-x 0.1 -y 0.5 -z 1 -a 0.3 -b 0.7 -g 0.1</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/flower.png">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/flower.png" alt="Input image" />
			</a>	
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/flower_poly.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/flower_poly.png" alt="Polygonalization" />
			</a>
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/flower_decomp.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/flower_decomp.png" alt="Convex decomposition" />
			</a>
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/flower_shape.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/flower_shape.png" alt="Digitized decomposition" />
			</a>
		</td>
    		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/flower_result.pmg">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/flower_result.png" alt="Transformed result" />
			</a>
		</td>  
		</tr>
		<tr>
			<td align="center" valign="center">  Input image </td>
			<td align="center" valign="center">  Polygon extraction </td>
			<td align="center" valign="center">  Convex decomposition </td>
			<td align="center" valign="center">  Digitized decomposition </td>
			<td align="center" valign="center">  Transformed result </td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/flower.pgm">leaf.pgm</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./transformDecomShape3d -i ../Dataset/leaf.pgm -o ../Dataset/leaf_result.pgm -e -a 0.1 -b 0.1 -t 0.314</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/leaf.png">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/leaf.png" alt="Input image" />
			</a>	
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/leaf_poly.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/leaf_poly.png" alt="Polygonalization" />
			</a>
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/leaf_decomp.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/leaf_decomp.png" alt="Convex decomposition" />
			</a>
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/leaf_shape.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/leaf_shape.png" alt="Digitized decomposition" />
			</a>
		</td>
    		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/leaf_result.pmg">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/leaf_result.png" alt="Transformed result" />
			</a>
		</td>  
		</tr>
		<tr>
			<td align="center" valign="center">  Input image </td>
			<td align="center" valign="center">  Polygon extraction </td>
			<td align="center" valign="center">  Convex decomposition </td>
			<td align="center" valign="center">  Digitized decomposition </td>
			<td align="center" valign="center">  Transformed result </td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/flower.pgm">snowflake.pgm</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./transformDecomShape3d -i ../Samples/snowflake.pgm -o ../Results/snowflake_result.pgm -e -a 0.12 -b 0.41 -t 0.14</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/snowflake.png">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/snowflake.png" alt="Input image" />
			</a>	
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/snowflake_poly.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/snowflake_poly.png" alt="Polygonalization" />
			</a>
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/snowflake_decomp.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/snowflake_decomp.png" alt="Convex decomposition" />
			</a>
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/snowflake_shape.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/snowflake_shape.png" alt="Digitized decomposition" />
			</a>
		</td>
    		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/snowflake_result.pmg">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/snowflake_result.png" alt="Transformed result" />
			</a>
		</td>  
		</tr>
		<tr>
			<td align="center" valign="center">  Input image </td>
			<td align="center" valign="center">  Polygon extraction </td>
			<td align="center" valign="center">  Convex decomposition </td>
			<td align="center" valign="center">  Digitized decomposition </td>
			<td align="center" valign="center">  Transformed result </td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/flower.pgm">hand.pgm</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./transformDecomShape3d -i ../Dataset/hand.pgm -o ../Dataset/hand_result.pgm -e -a 0.1 -b 0.1 -t 0.1</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/hand.png">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/hand.png" alt="Input image" />
			</a>	
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/hand_poly.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/hand_poly.png" alt="Polygonalization" />
			</a>
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/hand_decomp.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/hand_decomp.png" alt="Convex decomposition" />
			</a>
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/hand_shape.eps">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/hand_shape.png" alt="Digitized decomposition" />
			</a>
		</td>
    		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/hand_result.pmg">
				<img width="120" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/hand_result.png" alt="Transformed result" />
			</a>
		</td>  
		</tr>
		<tr>
			<td align="center" valign="center">  Input image </td>
			<td align="center" valign="center">  Polygon extraction </td>
			<td align="center" valign="center">  Convex decomposition </td>
			<td align="center" valign="center">  Digitized decomposition </td>
			<td align="center" valign="center">  Transformed result </td>
		</tr>
	</table>
</p>
