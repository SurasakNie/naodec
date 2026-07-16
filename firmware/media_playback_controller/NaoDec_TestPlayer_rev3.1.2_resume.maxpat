{
	"patcher": {
		"fileversion": 1,
		"appversion": {
			"major": 9,
			"minor": 1,
			"revision": 4,
			"architecture": "x64",
			"modernui": 1
		},
		"classnamespace": "box",
		"openrect": [ 150.0, 150.0, 920.0, 650.0 ],
		"toolbarvisible": 1,
		"boxes": [
			{
				"box": {
					"id": "obj-4",
					"maxclass": "comment",
					"linecount": 7,
					"numinlets": 1,
					"numoutlets": 0,
					"patching_rect": [ 500.0, 30.0, 390.0, 115.0 ],
					"text": "NAODEC TEST PLAYER - RESUME LOGIC\n1) Click [open] and choose a sound file\n2) Turn ezdac~ ON\n3) Play from stopped = start from beginning\n4) Play while playing = no action\n5) Pause then Play = resume; Stop then Play = restart\n6) Knob = volume"
				}
			},
			{
				"box": {
					"id": "obj-1",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 40.0, 30.0, 120.0, 22.0 ],
					"text": "udpreceive 9000"
				}
			},
			{
				"box": {
					"id": "obj-3",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 5,
					"outlettype": [ "", "", "", "", "" ],
					"patching_rect": [ 40.0, 110.0, 380.0, 22.0 ],
					"text": "route /transport/play /transport/pause /transport/stop /volume"
				}
			},
			{
				"box": {
					"bgcolor": [ 0.066666666666667, 0.501960784313725, 0.250980392156863, 1.0 ],
					"id": "obj-10",
					"maxclass": "button",
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [ "bang" ],
					"parameter_enable": 0,
					"patching_rect": [ 40.0, 160.0, 30.0, 30.0 ]
				}
			},
			{
				"box": {
					"id": "obj-12",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 0,
					"patching_rect": [ 75.0, 164.0, 80.0, 22.0 ],
					"text": "print PLAY"
				}
			},
			{
				"box": {
					"bgcolor": [ 0.843137254901961, 0.674509803921569, 0.337254901960784, 1.0 ],
					"id": "obj-20",
					"maxclass": "button",
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [ "bang" ],
					"parameter_enable": 0,
					"patching_rect": [ 190.0, 160.0, 30.0, 30.0 ]
				}
			},
			{
				"box": {
					"id": "obj-22",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 0,
					"patching_rect": [ 225.0, 164.0, 90.0, 22.0 ],
					"text": "print PAUSE"
				}
			},
			{
				"box": {
					"bgcolor": [ 0.501962602138519, 0.0, 0.008127611130476, 1.0 ],
					"id": "obj-30",
					"maxclass": "button",
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [ "bang" ],
					"parameter_enable": 0,
					"patching_rect": [ 340.0, 160.0, 30.0, 30.0 ]
				}
			},
			{
				"box": {
					"id": "obj-32",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 0,
					"patching_rect": [ 375.0, 164.0, 80.0, 22.0 ],
					"text": "print STOP"
				}
			},
			{
				"box": {
					"id": "obj-70",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 40.0, 210.0, 185.0, 22.0 ],
					"text": "value naodec_transport_state 0"
				}
			},
			{
				"box": {
					"id": "obj-71",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 4,
					"outlettype": [ "bang", "bang", "bang", "" ],
					"patching_rect": [ 40.0, 245.0, 65.0, 22.0 ],
					"text": "sel 0 1 2"
				}
			},
			{
				"box": {
					"id": "obj-72",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 2,
					"outlettype": [ "bang", "bang" ],
					"patching_rect": [ 40.0, 280.0, 45.0, 22.0 ],
					"text": "t b b"
				}
			},
			{
				"box": {
					"id": "obj-74",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 2,
					"outlettype": [ "bang", "bang" ],
					"patching_rect": [ 115.0, 280.0, 45.0, 22.0 ],
					"text": "t b b"
				}
			},
			{
				"box": {
					"id": "obj-11",
					"maxclass": "message",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 40.0, 320.0, 29.5, 22.0 ],
					"text": "1"
				}
			},
			{
				"box": {
					"id": "obj-73",
					"maxclass": "message",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 105.0, 320.0, 52.0, 22.0 ],
					"text": "resume"
				}
			},
			{
				"box": {
					"id": "obj-75",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 240.0, 210.0, 185.0, 22.0 ],
					"text": "value naodec_transport_state 0"
				}
			},
			{
				"box": {
					"id": "obj-76",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 2,
					"outlettype": [ "bang", "" ],
					"patching_rect": [ 240.0, 245.0, 40.0, 22.0 ],
					"text": "sel 1"
				}
			},
			{
				"box": {
					"id": "obj-77",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 2,
					"outlettype": [ "bang", "bang" ],
					"patching_rect": [ 240.0, 280.0, 45.0, 22.0 ],
					"text": "t b b"
				}
			},
			{
				"box": {
					"id": "obj-21",
					"maxclass": "message",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 240.0, 320.0, 45.0, 22.0 ],
					"text": "pause"
				}
			},
			{
				"box": {
					"id": "obj-78",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 2,
					"outlettype": [ "bang", "bang" ],
					"patching_rect": [ 340.0, 210.0, 45.0, 22.0 ],
					"text": "t b b"
				}
			},
			{
				"box": {
					"id": "obj-31",
					"maxclass": "message",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 340.0, 250.0, 29.5, 22.0 ],
					"text": "0"
				}
			},
			{
				"box": {
					"id": "obj-79",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 390.0, 355.0, 185.0, 22.0 ],
					"text": "value naodec_transport_state 0"
				}
			},
			{
				"box": {
					"id": "obj-80",
					"maxclass": "message",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 390.0, 285.0, 29.5, 22.0 ],
					"text": "1"
				}
			},
			{
				"box": {
					"id": "obj-81",
					"maxclass": "message",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 430.0, 285.0, 29.5, 22.0 ],
					"text": "2"
				}
			},
			{
				"box": {
					"id": "obj-82",
					"maxclass": "message",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 470.0, 285.0, 29.5, 22.0 ],
					"text": "0"
				}
			},
			{
				"box": {
					"format": 6,
					"id": "obj-40",
					"maxclass": "flonum",
					"numinlets": 1,
					"numoutlets": 2,
					"outlettype": [ "", "bang" ],
					"parameter_enable": 0,
					"patching_rect": [ 620.0, 160.0, 70.0, 22.0 ]
				}
			},
			{
				"box": {
					"id": "obj-43",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 0,
					"patching_rect": [ 700.0, 160.0, 70.0, 22.0 ],
					"text": "print VOL"
				}
			},
			{
				"box": {
					"id": "obj-41",
					"maxclass": "newobj",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "float" ],
					"patching_rect": [ 620.0, 200.0, 60.0, 22.0 ],
					"text": "* 127."
				}
			},
			{
				"box": {
					"id": "obj-42",
					"maxclass": "slider",
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"parameter_enable": 0,
					"patching_rect": [ 620.0, 240.0, 200.0, 25.0 ],
					"size": 128.0
				}
			},
			{
				"box": {
					"id": "obj-60",
					"maxclass": "newobj",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 750.0, 200.0, 70.0, 22.0 ],
					"text": "pack 0. 50"
				}
			},
			{
				"box": {
					"id": "obj-61",
					"maxclass": "newobj",
					"numinlets": 2,
					"numoutlets": 2,
					"outlettype": [ "signal", "bang" ],
					"patching_rect": [ 750.0, 240.0, 45.0, 22.0 ],
					"text": "line~"
				}
			},
			{
				"box": {
					"id": "obj-50",
					"maxclass": "message",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 120.0, 400.0, 40.0, 22.0 ],
					"text": "open"
				}
			},
			{
				"box": {
					"id": "obj-51",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 2,
					"outlettype": [ "signal", "bang" ],
					"patching_rect": [ 40.0, 450.0, 70.0, 22.0 ],
					"text": "sfplay~"
				}
			},
			{
				"box": {
					"id": "obj-52",
					"maxclass": "newobj",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "signal" ],
					"patching_rect": [ 40.0, 500.0, 50.0, 22.0 ],
					"text": "*~ 0."
				}
			},
			{
				"box": {
					"id": "obj-53",
					"maxclass": "ezdac~",
					"numinlets": 2,
					"numoutlets": 0,
					"patching_rect": [ 40.0, 550.0, 45.0, 45.0 ]
				}
			},
			{
				"box": {
					"id": "obj-54",
					"maxclass": "newobj",
					"numinlets": 1,
					"numoutlets": 1,
					"outlettype": [ "bang" ],
					"patching_rect": [ 750.0, 110.0, 60.0, 22.0 ],
					"text": "loadbang"
				}
			},
			{
				"box": {
					"id": "obj-55",
					"maxclass": "message",
					"numinlets": 2,
					"numoutlets": 1,
					"outlettype": [ "" ],
					"patching_rect": [ 750.0, 150.0, 35.0, 22.0 ],
					"text": "0.7"
				}
			}
		],
		"lines": [
			{ "patchline": { "destination": [ "obj-3", 0 ], "source": [ "obj-1", 0 ] } },
			{ "patchline": { "destination": [ "obj-10", 0 ], "source": [ "obj-3", 0 ] } },
			{ "patchline": { "destination": [ "obj-12", 0 ], "source": [ "obj-3", 0 ] } },
			{ "patchline": { "destination": [ "obj-70", 0 ], "source": [ "obj-10", 0 ] } },
			{ "patchline": { "destination": [ "obj-71", 0 ], "source": [ "obj-70", 0 ] } },
			{ "patchline": { "destination": [ "obj-72", 0 ], "source": [ "obj-71", 0 ] } },
			{ "patchline": { "destination": [ "obj-74", 0 ], "source": [ "obj-71", 2 ] } },
			{ "patchline": { "destination": [ "obj-11", 0 ], "source": [ "obj-72", 1 ] } },
			{ "patchline": { "destination": [ "obj-80", 0 ], "source": [ "obj-72", 0 ] } },
			{ "patchline": { "destination": [ "obj-73", 0 ], "source": [ "obj-74", 1 ] } },
			{ "patchline": { "destination": [ "obj-80", 0 ], "source": [ "obj-74", 0 ] } },
			{ "patchline": { "destination": [ "obj-51", 0 ], "source": [ "obj-11", 0 ] } },
			{ "patchline": { "destination": [ "obj-51", 0 ], "source": [ "obj-73", 0 ] } },
			{ "patchline": { "destination": [ "obj-20", 0 ], "source": [ "obj-3", 1 ] } },
			{ "patchline": { "destination": [ "obj-22", 0 ], "source": [ "obj-3", 1 ] } },
			{ "patchline": { "destination": [ "obj-75", 0 ], "source": [ "obj-20", 0 ] } },
			{ "patchline": { "destination": [ "obj-76", 0 ], "source": [ "obj-75", 0 ] } },
			{ "patchline": { "destination": [ "obj-77", 0 ], "source": [ "obj-76", 0 ] } },
			{ "patchline": { "destination": [ "obj-21", 0 ], "source": [ "obj-77", 1 ] } },
			{ "patchline": { "destination": [ "obj-81", 0 ], "source": [ "obj-77", 0 ] } },
			{ "patchline": { "destination": [ "obj-51", 0 ], "source": [ "obj-21", 0 ] } },
			{ "patchline": { "destination": [ "obj-30", 0 ], "source": [ "obj-3", 2 ] } },
			{ "patchline": { "destination": [ "obj-32", 0 ], "source": [ "obj-3", 2 ] } },
			{ "patchline": { "destination": [ "obj-78", 0 ], "source": [ "obj-30", 0 ] } },
			{ "patchline": { "destination": [ "obj-31", 0 ], "source": [ "obj-78", 1 ] } },
			{ "patchline": { "destination": [ "obj-82", 0 ], "source": [ "obj-78", 0 ] } },
			{ "patchline": { "destination": [ "obj-51", 0 ], "source": [ "obj-31", 0 ] } },
			{ "patchline": { "destination": [ "obj-79", 0 ], "source": [ "obj-80", 0 ] } },
			{ "patchline": { "destination": [ "obj-79", 0 ], "source": [ "obj-81", 0 ] } },
			{ "patchline": { "destination": [ "obj-79", 0 ], "source": [ "obj-82", 0 ] } },
			{ "patchline": { "destination": [ "obj-82", 0 ], "source": [ "obj-51", 1 ] } },
			{ "patchline": { "destination": [ "obj-40", 0 ], "source": [ "obj-3", 3 ] } },
			{ "patchline": { "destination": [ "obj-43", 0 ], "source": [ "obj-3", 3 ] } },
			{ "patchline": { "destination": [ "obj-41", 0 ], "source": [ "obj-40", 0 ] } },
			{ "patchline": { "destination": [ "obj-42", 0 ], "source": [ "obj-41", 0 ] } },
			{ "patchline": { "destination": [ "obj-60", 0 ], "source": [ "obj-40", 0 ] } },
			{ "patchline": { "destination": [ "obj-61", 0 ], "source": [ "obj-60", 0 ] } },
			{ "patchline": { "destination": [ "obj-52", 1 ], "source": [ "obj-61", 0 ] } },
			{ "patchline": { "destination": [ "obj-51", 0 ], "source": [ "obj-50", 0 ] } },
			{ "patchline": { "destination": [ "obj-82", 0 ], "source": [ "obj-50", 0 ] } },
			{ "patchline": { "destination": [ "obj-52", 0 ], "source": [ "obj-51", 0 ] } },
			{ "patchline": { "destination": [ "obj-53", 0 ], "source": [ "obj-52", 0 ] } },
			{ "patchline": { "destination": [ "obj-53", 1 ], "source": [ "obj-52", 0 ] } },
			{ "patchline": { "destination": [ "obj-55", 0 ], "source": [ "obj-54", 0 ] } },
			{ "patchline": { "destination": [ "obj-82", 0 ], "source": [ "obj-54", 0 ] } },
			{ "patchline": { "destination": [ "obj-40", 0 ], "source": [ "obj-55", 0 ] } }
		]
	}
}
