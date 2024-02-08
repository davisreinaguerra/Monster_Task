classdef monsterapp < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = public)
        
        % UI Properties
        UIFigure                            matlab.ui.Figure
        StartButton                         matlab.ui.control.Button
        SoundCheckBox                       matlab.ui.control.CheckBox
        MonsterCheckBox                     matlab.ui.control.CheckBox
        FibPhotCheckBox                     matlab.ui.control.CheckBox
        msLabel_3                           matlab.ui.control.Label
        msLabel_2                           matlab.ui.control.Label
        msLabel                             matlab.ui.control.Label
        RewardVolumeEditField               matlab.ui.control.NumericEditField
        RewardVolumeEditFieldLabel          matlab.ui.control.Label
        EnterTimeLimitEditField             matlab.ui.control.NumericEditField
        EnterTimeLimitLabel                 matlab.ui.control.Label
        IntertrialIntervalEditField         matlab.ui.control.NumericEditField
        IntertrialIntervalEditFieldLabel    matlab.ui.control.Label
        NumberofTrialsEditField             matlab.ui.control.NumericEditField
        NumberofTrialsEditFieldLabel        matlab.ui.control.Label
        DateEditField                       matlab.ui.control.EditField
        DateEditFieldLabel                  matlab.ui.control.Label
        AnimalCodeEditField                 matlab.ui.control.EditField
        AnimalCodeEditFieldLabel            matlab.ui.control.Label
        DayEditField                        matlab.ui.control.EditField
        DayEditFieldLabel                   matlab.ui.control.Label
        
        
        %Variables
        date
        animal_code
        day
        arduino_Obj
        n_trials
        sound_qm
        monster_qm
        fibphot_qm
        reward_volume
        intertrial_interval
        enter_time_limit
        start_qm
    end

    % Callbacks that handle component events
    methods (Access = private)

        % Button pushed function: StartButton
        function start(app, event)
            writeline(app.arduino_Obj, num2str(app.n_trials));
            writeline(app.arduino_Obj, num2str(app.intertrial_interval));
            writeline(app.arduino_Obj, num2str(app.enter_time_limit));
            writeline(app.arduino_Obj, num2str(app.reward_volume));
            writeline(app.arduino_Obj, num2str(app.monster_qm));
            writeline(app.arduino_Obj, num2str(app.sound_qm));
            writeline(app.arduino_Obj, "1");
            delete(app.UIFigure);
            delete(app);
        end

        % Value changed function: SoundCheckBox
        function sound_qm_check(app, event)
            value = app.SoundCheckBox.Value;
            app.sound_qm = value;
        end

        % Value changed function: MonsterCheckBox
        function monster_qm_check(app, event)
            value = app.MonsterCheckBox.Value;
            app.monster_qm = value;
        end

        % Value changed function: FibphotCheckBox
        function fibphot_qm_check(app, event)
            value = app.FibPhotCheckBox.Value;
            app.fibphot_qm = value;
            assignin("base", "run_fibphot", app.fibphot_qm);
        end

        % Value changed function: RewardVolumeEditField
        function reward_volume_enter(app, event)
            value = app.RewardVolumeEditField.Value;
            app.reward_volume = value;
            assignin("base", "reward_volume", app.reward_volume);
        end

        % Value changed function: EnterTimeLimitEditField
        function enter_time_limit_enter(app, event)
            value = app.EnterTimeLimitEditField.Value;
            app.enter_time_limit = value * 1000;
            assignin("base", "enter_time_limit", app.enter_time_limit);
        end

        % Value changed function: IntertrialIntervalEditField
        function intertrial_interval_enter(app, event)
            value = app.IntertrialIntervalEditField.Value;
            app.intertrial_interval = value * 1000;
            assignin("base", "intertrial_interval", app.intertrial_interval);
        end

        % Value changed function: NumberofTrialsEditField
        function n_trials_enter(app, event)
            value = app.NumberofTrialsEditField.Value;
            app.n_trials = value;
            assignin("base", "n_trials", app.n_trials);
        end


        %%%%%%%%%%%%%
        % Value changed function: DateEditField
        function date_enter(app, event)
            value = app.DateEditField.Value;
            app.date = value;
            assignin("base", "date_handle", app.date);
        end

        function animal_code_enter(app, event)
            value = app.AnimalCodeEditField.Value;
            app.animal_code = value;
            assignin("base", "animal_code_handle", app.animal_code);
        end

        function day_enter(app, event)
            value = app.DayEditField.Value;
            app.day = value;
            assignin("base", "day_handle", app.day);
        end


    end

    % Component initialization
    methods (Access = private)

        % Create UIFigure and components
        function createComponents(app)

            % Get the file path for locating images
            pathToMLAPP = fileparts(mfilename('fullpath'));

            % Create UIFigure and hide until all components are created
            app.UIFigure = uifigure('Visible', 'off');
            app.UIFigure.Position = [0 0 412 470];
            app.UIFigure.Name = 'MATLAB App';


            % Create DayEditFieldLabel
            app.DayEditFieldLabel = uilabel(app.UIFigure);
            app.DayEditFieldLabel.HorizontalAlignment = 'right';
            app.DayEditFieldLabel.FontSize = 18;
            app.DayEditFieldLabel.Position = [25 430 142 23];
            app.DayEditFieldLabel.Text = 'Day';

            % Create DayEditField
            app.DayEditField = uieditfield(app.UIFigure, 'text');
            app.DayEditField.ValueChangedFcn = createCallbackFcn(app, @day_enter, true);
            app.DayEditField.Placeholder = 'Training/Monster#';
            app.DayEditField.Position = [186 430 200 22];
            

            % Create AnimalCodeEditFieldLabel
            app.AnimalCodeEditFieldLabel = uilabel(app.UIFigure);
            app.AnimalCodeEditFieldLabel.HorizontalAlignment = 'right';
            app.AnimalCodeEditFieldLabel.FontSize = 18;
            app.AnimalCodeEditFieldLabel.Position = [25 400 142 23];
            app.AnimalCodeEditFieldLabel.Text = 'AnimalCode:';

            % Create AnimalCodeEditField
            app.AnimalCodeEditField = uieditfield(app.UIFigure, 'text');
            app.AnimalCodeEditField.ValueChangedFcn = createCallbackFcn(app, @animal_code_enter, true);
            app.AnimalCodeEditField.Placeholder = 'Monster*_0*';
            app.AnimalCodeEditField.Position = [186 400 200 22];

            
            % Create DateEditFieldLabel
            app.DateEditFieldLabel = uilabel(app.UIFigure);
            app.DateEditFieldLabel.HorizontalAlignment = 'right';
            app.DateEditFieldLabel.FontSize = 18;
            app.DateEditFieldLabel.Position = [25 370 142 23];
            app.DateEditFieldLabel.Text = 'Date:';

            % Create DateEditField
            app.DateEditField = uieditfield(app.UIFigure, 'text');
            app.DateEditField.ValueChangedFcn = createCallbackFcn(app, @date_enter, true);
            app.DateEditField.Placeholder = 'Month_Day_Year';
            app.DateEditField.Position = [186 370 200 22];

            %______________________Numeric Edit Fields ___________________

            % Create NumberofTrialsEditFieldLabel
            app.NumberofTrialsEditFieldLabel = uilabel(app.UIFigure);
            app.NumberofTrialsEditFieldLabel.HorizontalAlignment = 'right';
            app.NumberofTrialsEditFieldLabel.FontSize = 18;
            app.NumberofTrialsEditFieldLabel.Position = [25 340 142 23];
            app.NumberofTrialsEditFieldLabel.Text = 'Number of Trials:';

            % Create NumberofTrialsEditField
            app.NumberofTrialsEditField = uieditfield(app.UIFigure, 'numeric');
            app.NumberofTrialsEditField.ValueChangedFcn = createCallbackFcn(app, @n_trials_enter, true);
            app.NumberofTrialsEditField.Position = [186 340 58 22];


            % Create IntertrialIntervalEditFieldLabel
            app.IntertrialIntervalEditFieldLabel = uilabel(app.UIFigure);
            app.IntertrialIntervalEditFieldLabel.HorizontalAlignment = 'right';
            app.IntertrialIntervalEditFieldLabel.FontSize = 18;
            app.IntertrialIntervalEditFieldLabel.Position = [28 310 139 23];
            app.IntertrialIntervalEditFieldLabel.Text = 'Intertrial Interval:';

            % Create IntertrialIntervalEditField
            app.IntertrialIntervalEditField = uieditfield(app.UIFigure, 'numeric');
            app.IntertrialIntervalEditField.ValueChangedFcn = createCallbackFcn(app, @intertrial_interval_enter, true);
            app.IntertrialIntervalEditField.Position = [186 310 58 22];


            % Create EnterTimeLimitLabel
            app.EnterTimeLimitLabel = uilabel(app.UIFigure);
            app.EnterTimeLimitLabel.HorizontalAlignment = 'right';
            app.EnterTimeLimitLabel.FontSize = 18;
            app.EnterTimeLimitLabel.Position = [27 280 140 23];
            app.EnterTimeLimitLabel.Text = 'Enter Time Limit:';

            % Create EnterTimeLimitEditField
            app.EnterTimeLimitEditField = uieditfield(app.UIFigure, 'numeric');
            app.EnterTimeLimitEditField.ValueChangedFcn = createCallbackFcn(app, @enter_time_limit_enter, true);
            app.EnterTimeLimitEditField.Position = [186 280 58 22];


            % Create RewardVolumeEditFieldLabel
            app.RewardVolumeEditFieldLabel = uilabel(app.UIFigure);
            app.RewardVolumeEditFieldLabel.HorizontalAlignment = 'right';
            app.RewardVolumeEditFieldLabel.FontSize = 18;
            app.RewardVolumeEditFieldLabel.Position = [30 250 137 23];
            app.RewardVolumeEditFieldLabel.Text = 'Reward Volume:';

            % Create RewardVolumeEditField
            app.RewardVolumeEditField = uieditfield(app.UIFigure, 'numeric');
            app.RewardVolumeEditField.ValueChangedFcn = createCallbackFcn(app, @reward_volume_enter, true);
            app.RewardVolumeEditField.Position = [186 250 58 22];

            %____________msLabels________________________________

            % Create msLabel
            app.msLabel = uilabel(app.UIFigure);
            app.msLabel.HorizontalAlignment = 'left';
            app.msLabel.FontSize = 18;
            app.msLabel.Position = [250 310 29 23];
            app.msLabel.Text = 's';

            % Create msLabel_2
            app.msLabel_2 = uilabel(app.UIFigure);
            app.msLabel_2.HorizontalAlignment = 'left';
            app.msLabel_2.FontSize = 18;
            app.msLabel_2.Position = [250 280 29 23];
            app.msLabel_2.Text = 's';

            % Create msLabel_3
            app.msLabel_3 = uilabel(app.UIFigure);
            app.msLabel_3.HorizontalAlignment = 'left';
            app.msLabel_3.FontSize = 18;
            app.msLabel_3.Position = [250 250 29 23];
            app.msLabel_3.Text = 'ms';

            %______________Checkboxes______________________________________

            % Create MonsterCheckBox
            app.MonsterCheckBox = uicheckbox(app.UIFigure);
            app.MonsterCheckBox.ValueChangedFcn = createCallbackFcn(app, @monster_qm_check, true);
            app.MonsterCheckBox.Text = 'Monster';
            app.MonsterCheckBox.FontSize = 18;
            app.MonsterCheckBox.Position = [300 340 87 22];

            % Create SoundCheckBox
            app.SoundCheckBox = uicheckbox(app.UIFigure);
            app.SoundCheckBox.ValueChangedFcn = createCallbackFcn(app, @sound_qm_check, true);
            app.SoundCheckBox.Text = 'Sound';
            app.SoundCheckBox.FontSize = 18;
            app.SoundCheckBox.Position = [300 300 87 22];

            % Create FibphotCheckBox
            app.FibPhotCheckBox = uicheckbox(app.UIFigure);
            app.FibPhotCheckBox.ValueChangedFcn = createCallbackFcn(app, @fibphot_qm_check, true);
            app.FibPhotCheckBox.Text = 'FibPhot';
            app.FibPhotCheckBox.FontSize = 18;
            app.FibPhotCheckBox.Position = [300 260 87 22];

            %_____________Start Button_____________________________________

            % Create StartButton
            app.StartButton = uibutton(app.UIFigure, 'push');
            app.StartButton.ButtonPushedFcn = createCallbackFcn(app, @start, true);
            app.StartButton.Icon = fullfile(pathToMLAPP, 'run.png');
            app.StartButton.Position = [12 10 391 221];
            app.StartButton.Text = '';

            % Show the figure after all components are created
            app.UIFigure.Visible = 'on';
        end
    end

    % App creation and deletion
    methods (Access = public)

        % Construct app
        function app = monsterapp

            % Create UIFigure and components
            createComponents(app)

            % Register the app with App Designer
            registerApp(app, app.UIFigure)

            try
                app.arduino_Obj = serialport("COM5",9600);
                configureTerminator(app.arduino_Obj,"CR");
            catch ME
                app.arduino_Obj = [];
                disp(ME);
            end

            app.sound_qm = 0;
            app.monster_qm = 0;
            app.fibphot_qm = 0;
            app.start_qm = 0;

            app.date = "";
            app.animal_code = "";
            app.day = "Training1";
            assignin("base", "day_handle", app.day);

            if nargout == 0
                clear app
            end
        end

        % Code that executes before app deletion
        function delete(app)

            % Delete UIFigure when app is deleted
            delete(app.UIFigure)
        end
    end
end
