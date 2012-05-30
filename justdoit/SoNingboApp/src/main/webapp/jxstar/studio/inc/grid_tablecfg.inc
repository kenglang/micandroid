	config.eventcfg = {
		commitCfg: function(){
			var records = this.grid.getSelectionModel().getSelections();
			if (!JxUtil.selected(records)) return;
			
			for (var i = 0; i < records.length; i++) {
				var state = records[i].get('dm_tablecfg__state');
				if (!(state == '1' || state == '2' || state == '3')) {
					JxHint.alert(jx.dm.nomodify);	//'ѡ��ļ�¼�д���δ�޸ĵļ�¼�������ύ��'
					return true;
				}
			}
			
			var self = this;
			var hdcall = function() {
				//ȡѡ���¼������ֵ
				var params = 'funid='+ self.define.nodeid;
				for (var i = 0; i < records.length; i++) {
					params += '&keyid=' + records[i].get(self.define.pkcol);
				}

				//��������Ĳ���
				params += '&pagetype=editgrid&eventcode=commit';

				//ִ�д���������
				var endcall = function(data) {
					//���¼�������
					self.grid.getStore().reload();
				};

				//��������
				Request.postRequest(params, endcall);
			};
			//'������������Ϣ�޸����ݿ����ȷ���ύ��'
			Ext.Msg.confirm(jx.base.hint, jx.dm.modifydb, function(btn) {
				if (btn == 'yes') hdcall();
			});
		},
		
		cancelCfg: function(){
			var records = this.grid.getSelectionModel().getSelections();
			if (!JxUtil.selected(records)) return;
			
			for (var i = 0; i < records.length; i++) {
				var state = records[i].get('dm_tablecfg__state');
				if (!(state == '1' || state == '2' || state == '3')) {
					JxHint.alert(jx.dm.nomodify);	//'ѡ��ļ�¼�д���δ�޸ĵļ�¼�������ύ��'
					return true;
				}
			}
			
			var self = this;
			var hdcall = function() {
				//ȡѡ���¼������ֵ
				var params = 'funid='+ self.define.nodeid;
				for (var i = 0; i < records.length; i++) {
					params += '&keyid=' + records[i].get(self.define.pkcol);
				}

				//��������Ĳ���
				params += '&pagetype=editgrid&eventcode=cancel';

				//ִ�д���������
				var endcall = function(data) {
					//���¼�������
					self.grid.getStore().reload();
				};

				//��������
				Request.postRequest(params, endcall);
			};
			//'֮ǰ�޸ĵ�������Ϣ�����ָ�Ϊԭ��Ϣ��ȷ��ȡ����'
			Ext.Msg.confirm(jx.base.hint, jx.dm.cancelyes, function(btn) {
				if (btn == 'yes') hdcall();
			});
		},
		
		checkCfg: function(){
			var self = this;
			var records = this.grid.getSelectionModel().getSelections();
			if (!JxUtil.selectone(records)) return;
			
			var state = records[0].get('dm_tablecfg__state');
			if (!(state == '1' || state == '2' || state == '3')) {
				JxHint.alert(jx.dm.nocheck);	//'ѡ��ļ�¼δ�޸ģ�����Ҫ��֤��'
				return true;
			}
			
			var keyid = records[0].get(self.define.pkcol);
			var dsname = records[0].get('dm_tablecfg__ds_name');
			//�����������
			var params = 'funid='+ self.define.nodeid;
			params += '&keyid=' + keyid + '&ds_name=' + dsname + '&state=' + state;
			params += '&pagetype=editgrid&eventcode=check';
			
			//��ʾSQL���
			var checkForm = new Ext.form.FormPanel({
				border: false,
				frame: false,
				layout:'fit',
				labelAlign: 'top',
				baseCls: 'x-plain',
				items: [{xtype:'textarea', name:'dm_tablecfg__check_sql', border:false, 
						 style:'font-size:12px;border-width:0;line-height:20px;', readOnly:true}]
			});
			
			//������ʾ��֤SQL�ĶԻ���
			var checkWin = new Ext.Window({
				title:jx.dm.checksql,	//'��֤SQL'
				layout:'fit',
				width:500,
				height:500,
				resizable: true,
				modal: true,
				closeAction:'close',
				items:[checkForm],

				buttons: [{
					text:jx.dm.commit,	//'�ύ����'
					handler:function(){	//'������������Ϣ�޸����ݿ����ȷ���ύ��'
						Ext.Msg.confirm(jx.base.hint, jx.dm.modifydb, function(btn) {
							if (btn == 'yes') {
								var params1 = 'funid='+ self.define.nodeid + '&keyid=' + keyid;
								params1 += '&pagetype=editgrid&eventcode=commit';
								Request.postRequest(params1, function(data) {
									self.grid.getStore().reload();
								});
							}
						});
						//checkWin.close();
					}
				},{
					text:jx.base.close,	//'�ر�'
					handler:function(){checkWin.close();}
				}]
			});
		
			//��ʾ��֤SQL
			var endcall = function(data) {
				checkWin.show();
				var sql = data.sql;
				checkForm.getForm().findField('dm_tablecfg__check_sql').setValue(sql);
			};

			//��������
			Request.postRequest(params, endcall);
		}
	};
	
	config.initpage = function(gridNode){
		var grid = gridNode.page;
		//����༭ǰ�¼� 
		grid.on('beforeedit', function(event) {
			var r = event.record;
			var state = r.get('dm_tablecfg__state');
			//ɾ��״̬�ļ�¼�����޸�
			if (state == '3') {
				return false;
			}
			//����Ƿ��½�״̬��������Դ�����ռ䲻���޸�
			if (state != '1') {
				if (event.field == 'dm_tablecfg__table_space' || 
					event.field == 'dm_tablecfg__key_field') {
					return false;
				}
			}
			
			return true;
		});
		//����༭���¼�
		grid.on('afteredit', function(event) {
			if (event.field == 'dm_tablecfg__table_name') {
				var r = event.record;
				var tableid = r.get('dm_tablecfg__table_id');
				var keyfield = r.get('dm_tablecfg__key_field');
				
				if (tableid.length == 0 || (tableid.length > 0 && keyfield.length == 0)) {
					r.set('dm_tablecfg__key_field', event.value + '_id');
				}
			}
		});
		//��ʾ��ǰҳ��ʱ��ˢ�¼�¼
		JxUtil.delay(500, function(){
			var tabMain = grid.ownerCt.ownerCt;
			tabMain.on('tabchange', function(tabPanel, activeTab){
				var pagetype = activeTab.pagetype;
				if (pagetype == 'grid') {
					var gridCfg = activeTab.getComponent(0);
					gridCfg.getStore().reload();
				}
			});
		});
	};