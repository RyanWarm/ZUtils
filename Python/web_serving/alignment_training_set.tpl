<html>
<head>  
<meta http-equiv="content-type" content="text/html;charset=utf-8"> 
</head>
<body>
<pre>
</pre>

<button style='height:50px;color: yellow;background: blue;' onclick='javascript: document.location="alignment_run.py";'>Run alignment against Golden Data Set</button>
<br/>
<br/>

{% if offset-count >= 0 %}
<a href="alignment_training_set.py?offset={{offset-count}}&count={{count}}" >PreviousPage</a>
{% end %}
<a href="alignment_training_set.py?offset={{offset+count}}&count={{count}}" >NextPage</a>
<form action='alignment_training_set.py' method='get' >
<input type=hidden name=offset value={{offset}} />
<input type=hidden name=count value={{count}} />
<table border=1 cellpadding=0 style='margin:0;'>
<tr><td>CaseID</td><td>Group</td><td width=200px>UidList</td><td>ExpectedResult</td></tr>
{% for (id,info_map,uid_list_str,expected) in records %}
<tr>
    <td>{{id}}</td>
    <td><table cellpadding=0 style='margin:0;'><tr>{% for uid in info_map %} <td><a href='{{info_map[uid]['url']}}'><table cellpadding=0 style='margin:0;'><tr><td><img height=40px width=40px title="{{info_map[uid]['name']}}" src='{{info_map[uid]['image']}}' /></td></tr><tr><td><div style="width:40px;overflow:hidden;"><nobr>{{info_map[uid]['name']}}</nobr></div></td></tr></table></a></td>{% end %}</tr></table></td>
    <td><input name="case_{{id}}_list" size=100 value="{{uid_list_str}}"</td>
    <td>
    Match<input type='radio' name="case_{{id}}_expected" value='Y' {% if expected == 'Y' %}checked=1{% end %} />
    NoMatch<input type='radio' name="case_{{id}}_expected" value='N' {% if expected == 'N' %}checked=1{% end %} />
    </td>
</tr>
{% end %}
<tr>
    <td>New Case</td>
    <td></td>
    <td><input name="case_0_list" value=""</td>
    <td>
    Match<input type='radio' name="case_0_expected" value='Y'  />
    NoMatch<input type='radio' name="case_0_expected" value='N' />
    </td>
</tr>
<tr><td align=center colspan=4><input type=submit value="Submit Data "  /></td></tr>
</table>

</form>

<body>
</html>

