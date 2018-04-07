//  The following constant was designed to be supplied as an optional HTML parameter to the WiFiManagerParameter call for setting the city to be used
//  for the time zone setting.  This displays a pull-down list for selection on the configuration page for this parameter.  However, the default
//  input field box could not be turned off, so this was disabled until a mechanism to override this behavior in the WiFiManager library can be
//  established.
//
const char TimeZoneConfig[] = R"=====(
<label>Select city for time zone settings:
<select id=TZCity name=TZCity>
  <option value="Boston">    Boston......(UTC -05:00)</option>
  <option value="New York">  New York....(UTC -05:00)</option>
  <option value="Louisville">Louisville..(UTC -05:00)</option>
  <option value="Chicago">   Chicago.....(UTC -06:00)</option>
  <option value="Mountain">  Mountain....(UTC -07:00)</option>
  <option value="Pacific">   Pacific.....(UTC -08:00)</option>
  <option value="Alaska">    Alaska......(UTC -09:00)</option>
  <option value="Hawaii">    Hawaii......(UTC -10:00)</option>
</select> </label
)=====";
