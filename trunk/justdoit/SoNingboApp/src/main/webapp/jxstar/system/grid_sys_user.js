﻿Jxstar.currentPage = function() {
	var config = {param:{},initpage:function(page, define){},eventcfg:{}};

	var usersexData = Jxstar.findComboData('usersex');

	var cols = [
	{col:{header:'*姓名', width:65, sortable:true, editable:true, hcss:'color:#0000ff;',
		editor:new Ext.form.TextField({
			maxLength:20, allowBlank:false
		})}, field:{name:'sys_user__user_name',type:'string'}},
	{col:{header:'*工 号', width:100, sortable:true, editable:true, hcss:'color:#0000ff;',
		editor:new Ext.form.TextField({
			maxLength:20, allowBlank:false
		})}, field:{name:'sys_user__user_code',type:'string'}},
	{col:{header:'*部门编码', width:125, sortable:true, editable:true, hcss:'color:#0000ff;',
		editor:new Ext.form.TriggerField({
			maxLength:100,
			editable:false, allowBlank:false,
			triggerClass:'x-form-search-trigger', 
			onTriggerClick: function() {
				var selcfg = {pageType:'combogrid', nodeId:'sys_dept', layoutPage:'/public/layout/layout_tree.js', sourceField:'sys_dept.dept_code;dept_name;dept_id', targetField:'sys_dept.dept_code;dept_name;sys_user.dept_id', whereSql:"", whereValue:'', whereType:'', isSame:'0', isShowData:'1', isMoreSelect:'0',isReadonly:'1',fieldName:'sys_dept.dept_code'};
				Jxstar.createSelectWin(selcfg, this, 'node_sys_user_editgrid');
			}
		})}, field:{name:'sys_dept__dept_code',type:'string'}},
	{col:{header:'部门名称', width:129, sortable:true}, field:{name:'sys_dept__dept_name',type:'string'}},
	{col:{header:'职务', width:100, sortable:true, editable:true, hcss:'color:#3039b4;',
		editor:new Ext.form.TextField({
			maxLength:50
		})}, field:{name:'sys_user__duty',type:'string'}},
	{col:{header:'电话', width:100, sortable:true, editable:true, hcss:'color:#3039b4;',
		editor:new Ext.form.TextField({
			maxLength:20
		})}, field:{name:'sys_user__phone_code',type:'string'}},
	{col:{header:'性别', width:34, sortable:true, align:'center',
		editable:true, hcss:'color:#3039b4;',
		editor:new Ext.form.ComboBox({
			store: new Ext.data.SimpleStore({
				fields:['value','text'],
				data: usersexData
			}),
			emptyText: jx.star.select,
			mode: 'local',
			triggerAction: 'all',
			valueField: 'value',
			displayField: 'text',
			editable:false,
			value: usersexData[0][0]
		}),
		renderer:function(value){
			for (var i = 0; i < usersexData.length; i++) {
				if (usersexData[i][0] == value)
					return usersexData[i][1];
			}
		}}, field:{name:'sys_user__sex',type:'string'}},
	{col:{header:'邮箱', width:100, sortable:true, editable:true, hcss:'color:#3039b4;',
		editor:new Ext.form.TextField({
			maxLength:50
		})}, field:{name:'sys_user__email',type:'string'}},
	{col:{header:'是否注销', width:62, sortable:true, defaultval:'0', editable:true, hcss:'color:#3039b4;',
		editor:new Ext.form.Checkbox(),
		renderer:function(value) {
			return value=='1' ? jx.base.yes : jx.base.no;
		}}, field:{name:'sys_user__is_novalid',type:'string'}},
	{col:{header:'备注', width:172, sortable:true, editable:true, hcss:'color:#3039b4;',
		editor:new Ext.form.TextField({
			maxLength:200
		})}, field:{name:'sys_user__memo',type:'string'}},
	{col:{header:'用户ID', width:100, sortable:true, hidden:true}, field:{name:'sys_user__user_id',type:'string'}},
	{col:{header:'部门ID', width:100, sortable:true, hidden:true}, field:{name:'sys_user__dept_id',type:'string'}}
	];
	
	config.param = {
		cols: cols,
		sorts: null,
		hasQuery: '1',
		isedit: '1',
		isshow: '1',
		funid: 'sys_user'
	};
	
	config.eventcfg = {		

		setRole: function(){
			var records = this.grid.getSelectionModel().getSelections();
			if (!JxUtil.selectone(records)) return;

		},
			var userId = records[0].get(pkcol);
			JxUtil.setPass(userId);
	};
		
	return new Jxstar.GridNode(config);
}