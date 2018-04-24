# RigidTransformAcd3D

To install the program see <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/INSTALL.txt">INSTALL.txt</a> file


If you want you can also directly test the programm online:

http://ipol-geometry.loria.fr/~phuc/ipol_demo/DecompConvexRigidMotion/


* [![Build Status](https://travis-ci.org/ngophuc/RigidTransformAcd3D.svg?branch=master)](https://travis-ci.org/ngophuc/RigidTransformAcd3D)

# Program parameters

Allowed options are: 
<table align="right">
  <tr>
    <th align=Left>Options</th>
    <th align=Left>Description</th>
  </tr>
  <tr>
    <td align=Left>-h [ --help ]</th>
    <td>display this message.</th>
  </tr>	
  <tr>
    <td align=Left>-i [ --input ] arg</td>
    <td align=Left>input filename.</td>
  </tr>
  <tr>
    <td align=Left>-o [ --output ] arg (=./) </td>
    <td align=Left>output dir (default ./).</td>
  </tr>
  <tr>
    <td align=Left>-d [ --dir ] arg (=./) </td>
    <td align=Left> execute dir (default ./).</td>
  </tr>
  <tr>
    <td align=Left>-x [ --tx ] arg (=0) </td>
    <td align=Left>x-translation.</td>
  </tr>	
  <tr>
    <td align=Left>-y [ --ty ] arg (=0)</th>
    <td>y-translation.</th>
  </tr>	
  <tr>
    <td align=Left>-z [ --tz ] arg (=0)</td>
    <td align=Left>z-translation.</td>
  </tr>
  <tr>
    <td align=Left>-a [ --alpha ] arg (=0)  </td>
    <td align=Left>rotation angle by x-axis.</td>
  </tr>
  <tr>
    <td align=Left>-b [ --beta ] arg (=0) </td>
    <td align=Left>rotation angle by y-axis.</td>
  </tr>
  <tr>
    <td align=Left>-g [ --gamma ] arg (=0) </td>
    <td align=Left>rotation angle by z-axis.</td>
  </tr>	  
  <tr>
    <td align=Left>-s [ --scale ] arg (=100)   </td>
    <td align=Left>scale data.</td>
  </tr>
  <tr>
    <td align=Left>-r [ --resolution ] arg (=100000) </td>
    <td align=Left>decomposition parameter resolution.</td>
  </tr>
  <tr>
    <td align=Left>--depth arg (=20) </td>
    <td align=Left>decomposition parameter depth.</td>
  </tr>	  
  <tr>
    <td align=Left>-m [ --minVolumePerCH ] arg (=0.0001) </td>
    <td align=Left>decomposition parameter minimum volume of convex hull.</td>
  </tr>	
</table>

# Examples

<p>File <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/egea.obj">egea.obj</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./transformDecomShape3d -i ../Samples/egea.obj -o ../Results/egea_res.obj --resolution 1000000 
--depth 30 --minVolumePerCH 0.0 -x 0.1 -y 0.5 -z 1 -a 0.3 -b 0.7 -g 0.1</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/egea.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/egea.jpg" alt="Input image" />
			</a>	
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/egea_res_decomp.sdp">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/egea_res_decomp.jpg" alt="Convex decomposition" />
			</a>
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/egea_res_shape.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/egea_res_shape.jpg" alt="Digitized decomposition" />
			</a>
		</td>
    		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/egea_res_tshape.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/egea_res_tshape.jpg" alt="Transformed result" />
			</a>
		</td>  
		</tr>
		<tr>
			<td align="center" valign="center">  Input image </td>
			<td align="center" valign="center">  Convex decomposition </td>
			<td align="center" valign="center">  Digitized decomposition </td>
			<td align="center" valign="center">  Transformed result </td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/Hand1.obj">Hand1.obj</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./transformDecomShape3d -i ../Samples/Hand1.obj -o ../Results/Hand1_res.obj 
--resolution 90000 --depth 10 -s 0.5 -x 0.1 -y 0.5 -z 1 -a 0.3 -b 0.7 -g 0.1</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/Hand1.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/Hand1.jpg" alt="Input image" />
			</a>	
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/Hand1_res_decomp.sdp">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/Hand1_res_decomp.jpg" alt="Convex decomposition" />
			</a>
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/Hand1_res_shape.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/Hand1_res_shape.jpg" alt="Digitized decomposition" />
			</a>
		</td>
    		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/Hand1_res_tshape.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/Hand1_res_tshape.jpg" alt="Transformed result" />
			</a>
		</td>  
		</tr>
		<tr>
			<td align="center" valign="center">  Input image </td>
			<td align="center" valign="center">  Convex decomposition </td>
			<td align="center" valign="center">  Digitized decomposition </td>
			<td align="center" valign="center">  Transformed result </td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/drum.obj">drum.obj</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./transformDecomShape3d -i ../Samples/drum.obj -o ../Results/drum_res.obj 
--resolution 500000 --depth 40 -s 20 -x 0.1 -y 0.5 -z 1 -a 0.3</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/drum.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/drum.jpg" alt="Input image" />
			</a>	
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/drum_res_decomp.sdp">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/drum_res_decomp.jpg" alt="Convex decomposition" />
			</a>
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/drum_res_shape.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/drum_res_shape.jpg" alt="Digitized decomposition" />
			</a>
		</td>
    		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/drum_res_tshape.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/drum_res_tshape.jpg" alt="Transformed result" />
			</a>
		</td>  
		</tr>
		<tr>
			<td align="center" valign="center">  Input image </td>
			<td align="center" valign="center">  Convex decomposition </td>
			<td align="center" valign="center">  Digitized decomposition </td>
			<td align="center" valign="center">  Transformed result </td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/chair.obj">chair.obj</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./transformDecomShape3d -i ../Samples/chair.obj -o ../Results/chair_res.obj 
--resolution 500000 --depth 40 -s 100 -x 0.1 -y 0.5 -z 1 -b 0.3 -g 1.34</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/chair.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Samples/chair.jpg" alt="Input image" />
			</a>	
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/chair_res_decomp.sdp">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/chair_res_decomp.jpg" alt="Convex decomposition" />
			</a>
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/chair_res_shape.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/chair_res_shape.jpg" alt="Digitized decomposition" />
			</a>
		</td>
    		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/chair_res_tshape.obj">
				<img width="200" src="https://github.com/ngophuc/RigidTransformAcd3D/blob/master/Results/chair_res_tshape.jpg" alt="Transformed result" />
			</a>
		</td>  
		</tr>
		<tr>
			<td align="center" valign="center">  Input image </td>
			<td align="center" valign="center">  Convex decomposition </td>
			<td align="center" valign="center">  Digitized decomposition </td>
			<td align="center" valign="center">  Transformed result </td>
		</tr>
	</table>
</p>
