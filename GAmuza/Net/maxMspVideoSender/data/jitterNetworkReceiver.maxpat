{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 5,
			"minor" : 1,
			"revision" : 9
		}
,
		"rect" : [ 112.0, 273.0, 462.0, 435.0 ],
		"bglocked" : 0,
		"defrect" : [ 112.0, 273.0, 462.0, 435.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "port 8888",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 96.0, 96.0, 58.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"id" : "obj-17",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "ip 127.0.0.1",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 19.0, 96.0, 69.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"id" : "obj-20",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "<https://github.com/bakercp/ofxJitterNetworkSender>",
					"fontname" : "Arial",
					"patching_rect" : [ 107.0, 40.0, 299.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0,
					"id" : "obj-2",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op !- @val 255",
					"outlettype" : [ "jit_matrix", "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 270.0, 230.333344, 126.0, 20.0 ],
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"id" : "obj-16",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "\"sent from of => 21252\"",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 37.0, 189.0, 179.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0,
					"id" : "obj-7",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ofxJitterNetworkSender OF ADDON ",
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 11.0, 398.0, 34.0 ],
					"numinlets" : 1,
					"fontsize" : 24.0,
					"id" : "obj-6",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.fpsgui",
					"outlettype" : [ "", "" ],
					"mode" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 19.0, 382.333313, 80.0, 35.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"id" : "obj-14",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.fpsgui",
					"outlettype" : [ "", "" ],
					"mode" : 3,
					"fontname" : "Arial",
					"patching_rect" : [ 19.0, 344.333313, 80.0, 35.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"id" : "obj-12",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.fpsgui",
					"outlettype" : [ "", "" ],
					"mode" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 19.0, 306.333344, 80.0, 35.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"id" : "obj-3",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 124.0, 163.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"id" : "obj-1",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print",
					"fontname" : "Arial",
					"patching_rect" : [ 304.0, 189.0, 33.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"id" : "obj-4",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.fpsgui",
					"outlettype" : [ "", "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 19.0, 268.0, 80.0, 35.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"id" : "obj-21",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"outlettype" : [ "int" ],
					"patching_rect" : [ 229.0, 189.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"id" : "obj-22",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route connected",
					"outlettype" : [ "", "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 229.0, 163.0, 94.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"id" : "obj-23",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.net.recv @ip 127.0.0.1 @port 8888",
					"outlettype" : [ "jit_matrix", "", "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 19.0, 130.0, 203.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"id" : "obj-25",
					"numoutlets" : 3
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.pwindow",
					"outlettype" : [ "", "" ],
					"background" : 1,
					"patching_rect" : [ 270.0, 268.0, 160.0, 120.0 ],
					"numinlets" : 1,
					"dstrect" : [ 0, 0, 160, 120 ],
					"id" : "obj-15",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.pwindow",
					"outlettype" : [ "", "" ],
					"presentation_rect" : [ 15.0, 15.0, 160.0, 120.0 ],
					"background" : 1,
					"patching_rect" : [ 104.0, 268.0, 160.0, 120.0 ],
					"numinlets" : 1,
					"dstrect" : [ 0, 0, 160, 120 ],
					"id" : "obj-40",
					"numoutlets" : 2
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-25", 1 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 120.5, 156.0, 133.5, 156.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [ 28.5, 217.666672, 279.5, 217.666672 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [ 28.5, 158.0, 28.5, 158.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 2 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [ 212.5, 156.0, 238.5, 156.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-40", 0 ],
					"hidden" : 0,
					"midpoints" : [ 28.5, 218.5, 113.5, 218.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 1 ],
					"destination" : [ "obj-7", 1 ],
					"hidden" : 0,
					"midpoints" : [ 120.5, 156.0, 155.0, 156.0, 155.0, 156.0, 206.5, 156.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"midpoints" : [ 105.5, 122.0, 28.5, 122.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 1 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
