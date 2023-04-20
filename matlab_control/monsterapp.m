classdef monsterapp < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = public)
        UIFigure                      matlab.ui.Figure
        StartButton                   matlab.ui.control.Button
        SoundCheckBox                 matlab.ui.control.CheckBox
        MonsterCheckBox               matlab.ui.control.CheckBox
        msLabel_3                     matlab.ui.control.Label
        msLabel_2                     matlab.ui.control.Label
        msLabel                       matlab.ui.control.Label
        RewardVolumeEditField         matlab.ui.control.NumericEditField
        RewardVolumeEditFieldLabel    matlab.ui.control.Label
        EnterTimeLimitEditField       matlab.ui.control.NumericEditField
        EnterTimeLimitLabel           matlab.ui.control.Label
        IntertrialIntervalEditField   matlab.ui.control.NumericEditField
        IntertrialIntervalEditFieldLabel  matlab.ui.control.Label
        NumberofTrialsEditField       matlab.ui.control.NumericEditField
        NumberofTrialsEditFieldLabel  matlab.ui.control.Label
        arduino_Obj
        n_trials
        sound_qm
        monster_qm
        reward_volume
        intertrial_interval
        enter_time_limit
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

        % Value changed function: RewardVolumeEditField
        function reward_volume_enter(app, event)
            value = app.RewardVolumeEditField.Value;
            app.reward_volume = value;
        end

        % Value changed function: EnterTimeLimitEditField
        function enter_time_limit_enter(app, event)
            value = app.EnterTimeLimitEditField.Value;
            app.enter_time_limit = value;
        end

        % Value changed function: IntertrialIntervalEditField
        function intertrial_interval_enter(app, event)
            value = app.IntertrialIntervalEditField.Value;
            app.intertrial_interval = value;
        end

        % Value changed function: NumberofTrialsEditField
        function n_trials_enter(app, event)
            value = app.NumberofTrialsEditField.Value;
            app.n_trials = value;
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
            app.UIFigure.Position = [100 100 412 380];
            app.UIFigure.Name = 'MATLAB App';

            % Create NumberofTrialsEditFieldLabel
            app.NumberofTrialsEditFieldLabel = uilabel(app.UIFigure);
            app.NumberofTrialsEditFieldLabel.HorizontalAlignment = 'right';
            app.NumberofTrialsEditFieldLabel.FontSize = 18;
            app.NumberofTrialsEditFieldLabel.Position = [25 343 142 23];
            app.NumberofTrialsEditFieldLabel.Text = 'Number of Trials:';

            % Create NumberofTrialsEditField
            app.NumberofTrialsEditField = uieditfield(app.UIFigure, 'numeric');
            app.NumberofTrialsEditField.ValueChangedFcn = createCallbackFcn(app, @n_trials_enter, true);
            app.NumberofTrialsEditField.Position = [186 343 58 22];

            % Create IntertrialIntervalEditFieldLabel
            app.IntertrialIntervalEditFieldLabel = uilabel(app.UIFigure);
            app.IntertrialIntervalEditFieldLabel.HorizontalAlignment = 'right';
            app.IntertrialIntervalEditFieldLabel.FontSize = 18;
            app.IntertrialIntervalEditFieldLabel.Position = [28 312 139 23];
            app.IntertrialIntervalEditFieldLabel.Text = 'Intertrial Interval:';

            % Create IntertrialIntervalEditField
            app.IntertrialIntervalEditField = uieditfield(app.UIFigure, 'numeric');
            app.IntertrialIntervalEditField.ValueChangedFcn = createCallbackFcn(app, @intertrial_interval_enter, true);
            app.IntertrialIntervalEditField.Position = [186 312 58 22];

            % Create EnterTimeLimitLabel
            app.EnterTimeLimitLabel = uilabel(app.UIFigure);
            app.EnterTimeLimitLabel.HorizontalAlignment = 'right';
            app.EnterTimeLimitLabel.FontSize = 18;
            app.EnterTimeLimitLabel.Position = [27 279 140 23];
            app.EnterTimeLimitLabel.Text = 'Enter Time Limit:';

            % Create EnterTimeLimitEditField
            app.EnterTimeLimitEditField = uieditfield(app.UIFigure, 'numeric');
            app.EnterTimeLimitEditField.ValueChangedFcn = createCallbackFcn(app, @enter_time_limit_enter, true);
            app.EnterTimeLimitEditField.Position = [186 279 58 22];

            % Create RewardVolumeEditFieldLabel
            app.RewardVolumeEditFieldLabel = uilabel(app.UIFigure);
            app.RewardVolumeEditFieldLabel.HorizontalAlignment = 'right';
            app.RewardVolumeEditFieldLabel.FontSize = 18;
            app.RewardVolumeEditFieldLabel.Position = [30 244 137 23];
            app.RewardVolumeEditFieldLabel.Text = 'Reward Volume:';

            % Create RewardVolumeEditField
            app.RewardVolumeEditField = uieditfield(app.UIFigure, 'numeric');
            app.RewardVolumeEditField.ValueChangedFcn = createCallbackFcn(app, @reward_volume_enter, true);
            app.RewardVolumeEditField.Position = [186 244 58 22];

            % Create msLabel
            app.msLabel = uilabel(app.UIFigure);
            app.msLabel.HorizontalAlignment = 'right';
            app.msLabel.FontSize = 18;
            app.msLabel.Position = [243 312 29 23];
            app.msLabel.Text = 'ms';

            % Create msLabel_2
            app.msLabel_2 = uilabel(app.UIFigure);
            app.msLabel_2.HorizontalAlignment = 'right';
            app.msLabel_2.FontSize = 18;
            app.msLabel_2.Position = [243 279 29 23];
            app.msLabel_2.Text = 'ms';

            % Create msLabel_3
            app.msLabel_3 = uilabel(app.UIFigure);
            app.msLabel_3.HorizontalAlignment = 'right';
            app.msLabel_3.FontSize = 18;
            app.msLabel_3.Position = [243 244 29 23];
            app.msLabel_3.Text = 'ms';

            % Create MonsterCheckBox
            app.MonsterCheckBox = uicheckbox(app.UIFigure);
            app.MonsterCheckBox.ValueChangedFcn = createCallbackFcn(app, @monster_qm_check, true);
            app.MonsterCheckBox.Text = 'Monster';
            app.MonsterCheckBox.FontSize = 18;
            app.MonsterCheckBox.Position = [293 312 87 22];

            % Create SoundCheckBox
            app.SoundCheckBox = uicheckbox(app.UIFigure);
            app.SoundCheckBox.ValueChangedFcn = createCallbackFcn(app, @sound_qm_check, true);
            app.SoundCheckBox.Text = 'Sound';
            app.SoundCheckBox.FontSize = 18;
            app.SoundCheckBox.Position = [300 279 74 22];

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
                app.arduino_Obj = serialport("COM13",9600);
                configureTerminator(app.arduino_Obj,"CR");
            catch ME
                app.arduino_Obj = [];
                disp(ME);
            end

            app.sound_qm = 0;
            app.monster_qm = 0;

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