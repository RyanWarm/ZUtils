<html>
<head>  
<meta http-equiv="content-type" content="text/html;charset=utf-8"> 
</head>
<body>

<a href="alignment_training_set.py">Back to Dataset</a><br/><br/>
<pre>
Precision: {{precision*100}}%
Recall:    {{recall*100}}%
</pre>
<table border=1>
<tr><td>CaseID</td><td>Group</td><td width=200px>UidList</td><td>ExpectedResult</td><td>ExperimentCorrectness</td></tr>
{% for (id,info_map,uid_list_str,expected,experiment) in records %}
<tr>
    <td>{{id}}</td>
    <td><table cellpadding=0 style='margin:0;'><tr>{% for uid in info_map %} <td><a href='{{info_map[uid]['url']}}'><table cellpadding=0 style='margin:0;'><tr><td><img height=40px width=40px title="{{info_map[uid]['name']}}" src='{{info_map[uid]['image']}}' /></td></tr><tr><td><div style="width:40px;overflow:hidden;"><nobr>{{info_map[uid]['name']}}</nobr></div></td></tr></table></a></td>{% end %}</tr></table></td>
    <td><div style="width:500px;overflow:hidden;"><nobr>{{uid_list_str}}</nobr></div></td>
    <td>
    {% if expected == 'Y' %} Match {% else %} NoMatch {% end %}
    </td>
    <td>
    {% if expected == experiment %} <font color='green'>Correct</font>{% else %} <font color='red'>Incorrect</font> {% end %}
    </td>
</tr>
{% end %}
</table>

<body>
</html>

