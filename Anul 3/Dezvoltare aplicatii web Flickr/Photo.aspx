<%@ Page Language="C#" MasterPageFile="~/MasterPagePhoto.master" AutoEventWireup="true" CodeFile="Photo.aspx.cs" Inherits="Photo" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
<script src="Scripts/jquery-1.10.2.min.js" ></script>

<script runat="server">

    int currentId = -1;
    int userId;
    int ownerId;
    int albumId;

    void Page_Load(object sender, EventArgs e)
    {
        int.TryParse(Request.QueryString["photoId"], out currentId);
        userId = getUserId();

        if (isPhotoValid())
        {
            /*
            if (!IsPostBack)
            {
                AlbumNameTextBox.Text = getAlbumName();
            }
            loadPhotos();*/
            loadComments();
        }
        else
        {
            System.Xml.XmlDocument doc = new System.Xml.XmlDocument();// XDSPhoto.GetXmlDocument();
            doc.LoadXml("<Comments></Comments>");

            doc.Save(Server.MapPath("~/App_Data/tempPhoto.xml"));
            //XDSPhoto.Data = doc.InnerXml;
            XDSComment.DataFile = Server.MapPath("~/App_Data/tempPhoto.xml");
            //XDSPhoto.Data = xDoc.InnerXml;
            XDSComment.DataBind();
            XDSComment.Save();
            
            String imageData = "/Assets/empty_image.jpg";
            //Page.ClientScript.RegisterStartupScript(this.GetType(), "loadImage", string.Format("document.getElementById(\"uploadedImage\").src = {0};alert('ceva');", imageData), true);
            //Page.ClientScript.RegisterStartupScript(this.GetType(), "cevaAlerta", string.Format("<script type=text/javascript>alert('ceva');</" + "/script>", imageData), true);
            StringBuilder cstext1 = new StringBuilder();
            //cstext1.Append("<script type='text/javascript' > alert('ceva2'); </");
            cstext1.Append("<script type=text/javascript > $(document).ready(function() { document.getElementById('uploadedImage').src = '" + imageData + "';}); </");
            cstext1.Append("script>");
            //Page.ClientScript.RegisterStartupScript(typeof(Page), "some", cstext1.ToString());
            uploadedImage.Src = imageData;
            System.Diagnostics.Debug.WriteLine("sent empty image");
        }
        btnAddComment.DataBind();
        btnDeletePhoto.DataBind();
        commentTextArea.DataBind();
        btnSave.DataBind();
        controls.DataBind();
    }

    int getUserId()
    {
        if (Context.User.Identity.IsAuthenticated)
        {
            try
            {
                System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                con.Open();
                string strQuery = "select [Id] from [dbo].[users] where [username]=@username";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                cmd.Parameters.AddWithValue("@username", System.Data.SqlDbType.Int).Value = Context.User.Identity.GetUserName();
                System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

                if (myReader.Read())
                {
                    // Assuming your desired value is the name as the 3rd field
                    int id = -1;
                    int.TryParse(myReader["Id"].ToString(), out id);
                    myReader.Close();
                    con.Close();
                    return id;
                }

                myReader.Close();
                con.Close();
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
            }
        }
        return -1;
    }

    Boolean checkedPhoto;
    Boolean photoValid;
    
    Boolean isPhotoValid()
    {
        if (!checkedPhoto)
        {
            checkedPhoto = true;
            photoValid = false;
            if (currentId > 0)
            {
                try
                {
                    System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                    con.Open();
                    string strQuery = "select * from [dbo].[photos] where [Id]=@id";
                    System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                    cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
                    System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

                    if (myReader.Read())
                    {
                        // Assuming your desired value is the name as the 3rd field
                        Models.PhotoDB photo = readerToPhotoDB(myReader);
                        //uploadedImage.Attributes["src"] = "data:image/" + photo.PhotoType + ";base64," + photo.Photo;
                        String imageData = "data:image/" + photo.PhotoType + ";base64," + photo.Photo;
                        StringBuilder cstext1 = new StringBuilder();
                        //cstext1.Append("<script type='text/javascript' > alert('ceva2'); </");
                        cstext1.Append("<script type=text/javascript > $(document).ready(function() { document.getElementById('uploadedImage').src = '" + imageData + "';}); </");
                        cstext1.Append("script>");
                        //Page.ClientScript.RegisterStartupScript(typeof(Page), "some", cstext1.ToString());
                        uploadedImage.Src = imageData;

                        //System.Diagnostics.Debug.WriteLine("sent some image");
                        ownerId = photo.User;
                        albumId = photo.Album;

                        myReader.Close();
                        con.Close();
                        photoValid = true;
                        return true;
                    }

                    myReader.Close();
                    con.Close();
                }
                catch (Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine(ex.ToString());
                }
            }
        }
        else
        {
            return photoValid;
        }
        return false;
    }

    byte[] Photo;
    
    private Models.PhotoDB readerToPhotoDB(System.Data.SqlClient.SqlDataReader myReader)
    {
        Models.PhotoDB newPhoto = new Models.PhotoDB();

        newPhoto.ID = int.Parse(myReader["Id"].ToString());
        newPhoto.PhotoType = myReader["photoType"].ToString();
        newPhoto.Category = myReader["category"].ToString();
        newPhoto.Description = myReader["description"].ToString();
        newPhoto.User = int.Parse(myReader["user"].ToString());
        newPhoto.Album = int.Parse(myReader["album"].ToString());

        //considering "photo's" bytes are on 2nd column
        Photo = (byte[])myReader.GetValue(2);

        string base64String = Convert.ToBase64String(Photo, 0, Photo.Length);
        newPhoto.Photo = base64String;

        return newPhoto;
    }
    
    void loadComments()
    {
        List<Models.CommentDB> list = getComments();

        System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
        doc.LoadXml("<Comments></Comments>");
        System.Xml.XmlNode rootNode = doc.SelectSingleNode("Comments");

        foreach (Models.CommentDB comment in list)
        {
            System.Xml.XmlAttribute xmlId = doc.CreateAttribute("Id");
            xmlId.Value = comment.ID.ToString();

            System.Xml.XmlAttribute xmlText = doc.CreateAttribute("text");
            xmlText.Value = comment.Text;

            System.Xml.XmlAttribute xmlPhoto = doc.CreateAttribute("photo");
            xmlPhoto.Value = comment.Photo.ToString();

            System.Xml.XmlAttribute xmlUser = doc.CreateAttribute("user");
            xmlUser.Value = comment.User.ToString();

            
            System.Xml.XmlNode xmlNode = doc.CreateNode(System.Xml.XmlNodeType.Element, "Comment", "");
            xmlNode.Attributes.Append(xmlId);
            xmlNode.Attributes.Append(xmlText);
            xmlNode.Attributes.Append(xmlPhoto);
            xmlNode.Attributes.Append(xmlUser);
            rootNode.AppendChild(xmlNode);
        }


        //System.Xml.XmlDocument xDoc = new System.Xml.XmlDocument();
        //xDoc.LoadXml(xml.Value);

        doc.Save(Server.MapPath("~/App_Data/tempPhoto.xml"));
        //XDSPhoto.Data = doc.InnerXml;
        XDSComment.DataFile = Server.MapPath("~/App_Data/tempPhoto.xml");
        XDSComment.DataBind();
        XDSComment.Save();
        //XDSMovie.Data
    }

    private List<Models.CommentDB> getComments()
    {
        List<Models.CommentDB> commentsList = new List<Models.CommentDB>();

        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select * from [dbo].[comments] where [photo]=@id order by [Id] desc";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            while (myReader.Read())
            {
                commentsList.Add(readerToCommentDB(myReader));
            }

            myReader.Close();
            con.Close();
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
        return commentsList;
    }

    private Models.CommentDB readerToCommentDB(System.Data.SqlClient.SqlDataReader myReader)
    {
        Models.CommentDB comment = new Models.CommentDB();

        comment.ID = int.Parse(myReader["Id"].ToString());
        comment.Text = myReader["text"].ToString().Replace("\n", "<br/>");
        comment.Photo = int.Parse(myReader["photo"].ToString());
        comment.User = int.Parse(myReader["user"].ToString());

        return comment;
    }

    void btnAddComment_Click(object sender, EventArgs e)
    {
        insertComment();
        loadComments();
        commentTextArea.InnerText = "";
    }

    void btnDeletePhoto_Click(object sender, EventArgs e)
    {
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "delete from [dbo].[photos] where [Id]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = currentId;
            cmd.ExecuteNonQuery();
            con.Close();
            Response.Redirect("~/Album?albumId=" + albumId);
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
    }
    
    void insertComment()
    {
        if (commentTextArea.InnerText.Length > 0)
        {
            try
            {
                System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                con.Open();
                //insert the file into database
                string strQuery = "insert into [dbo].[comments] ([text], [user], [photo]) values (@text, @user, @photo);SELECT CAST(scope_identity() AS int)";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                cmd.Parameters.Add("@text", System.Data.SqlDbType.VarChar).Value = commentTextArea.InnerText;
                cmd.Parameters.Add("@user", System.Data.SqlDbType.Int).Value = userId;
                cmd.Parameters.Add("@photo", System.Data.SqlDbType.Int).Value = currentId;
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (Exception ex)
            {
                //Response.Write(ex.Message);
                System.Diagnostics.Debug.WriteLine(ex.ToString());
            }
        }
        else
        {
        }
    }

    string getUsernameById(string id)
    {
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select [username] from [dbo].[users] where [Id]=@id order by [Id] desc";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = int.Parse(id);
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            if (myReader.Read())
            {
                string name = myReader["username"].ToString();
                myReader.Close();
                con.Close();
                return name;
            }

            myReader.Close();
            con.Close();
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
        return "";
    }
    
    bool canDeleteComment(String commenterId)
    {
        int id = int.Parse(commenterId);
        //if the current user is the owner of the photo
        if(userId == ownerId)
        {
            return true;
        }
        //if the current user wrote the comment
        if(userId == id)
        {
            return true;
        }
        return false;
    }

    bool canDeletePhoto()
    {
        //if the current user is the owner of the photo
        if (userId == ownerId && isPhotoValid())
        {
            return true;
        }
        return false;
    }

    Boolean canAddComment()
    {
        //if the current user is the owner of the photo
        if (userId != -1 && isPhotoValid())
        {
            return true;
        }
        return false;
    }


    void btnSavePhoto_Click(object sender, EventArgs e)
    {

        System.IO.MemoryStream ms = new System.IO.MemoryStream(Photo);
        System.Drawing.Image orgImg = System.Drawing.Image.FromStream(ms);
        float scaleCrop = float.Parse(hiddenScale.Value.ToString());
        int width = (int)((float)(scaleCrop * 400.0f));
        int height = (int)((float)(scaleCrop * 300.0f));
        
        System.Diagnostics.Debug.WriteLine(hiddenX.Value.ToString() + " " + hiddenY.Value.ToString() + " " + width + " " + height);
        
        System.Drawing.Rectangle areaToCrop = new System.Drawing.Rectangle(
                Convert.ToInt32(hiddenX.Value.ToString()),
                Convert.ToInt32(hiddenY.Value.ToString()),
                Convert.ToInt32(width),
                Convert.ToInt32(height));
        
        System.Drawing.Bitmap bitMap = new System.Drawing.Bitmap(areaToCrop.Width, areaToCrop.Height);
        //Create graphics object for alteration
        using (System.Drawing.Graphics g = System.Drawing.Graphics.FromImage(bitMap))
        {
            //Draw image to screen
            g.DrawImage(orgImg, new System.Drawing.Rectangle(0, 0, bitMap.Width, bitMap.Height), areaToCrop, System.Drawing.GraphicsUnit.Pixel);
        }
        System.IO.MemoryStream ms2 = new System.IO.MemoryStream();
        bitMap.Save(ms2, orgImg.RawFormat);// System.Drawing.Imaging.ImageFormat.Jpeg);
        orgImg.Dispose();

        System.Diagnostics.Debug.WriteLine("save data: " + Convert.ToBase64String(ms2.ToArray(), 0, ms2.ToArray().Length));
        
        Photo = ms2.ToArray();
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "update [dbo].[photos] set[photo]=@photo where [Id]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.Add("@photo", System.Data.SqlDbType.Binary).Value = Photo;
            cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = currentId;
            cmd.ExecuteNonQuery();
            con.Close();
            Response.Redirect("~/Album?albumId=" + albumId);
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
    }
    
    
</script>

    

    <link href='../css/jquery.guillotine.css' media='all' rel='stylesheet'>
  <link href='demo.css' media='all' rel='stylesheet'>
  <meta name='viewport' content='width=device-width, initial-scale=1.0, target-densitydpi=device-dpi'>
  <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <div id='content'>
    <div class='frame'>
      <img id='uploadedImage' src='http://lorempixel.com/640/480/city' runat="server"/>
            <!--<asp:Image ID="uploadedImage3" runat="server" ImageUrl="~/Assets/empty_image.jpg"/>-->
    </div>

    <div id='controls' runat="server" style='<%# canDeletePhoto() && canAddComment() ? "" : "display:none"%>'>
      <button id='rotate_left'  type='button' title='Rotate left'> &lt; </button>
      <button id='zoom_out'     type='button' title='Zoom out'> - </button>
      <button id='fit'          type='button' title='Fit image'> [ ]  </button>
      <button id='zoom_in'      type='button' title='Zoom in'> + </button>
      <button id='rotate_right' type='button' title='Rotate right'> &gt; </button>
    </div>
        
    <ul id='data'>
      <div class='column'>
        <li>x: <span runat="server" id='x'></span></li>
        <li>y: <span runat="server" id='y'></span></li>
      </div>
      <div class='column'>
        <li>width:  <span id='w'></span></li>
        <li>height: <span id='h'></span></li>
      </div>
      <div class='column'>
        <li>scale: <span runat="server" id='scale'></span></li>
        <li>angle: <span runat="server" id='angle'></span></li>
      </div>
    </ul>

        <form id="form1" runat="server">
            <asp:HiddenField ID="hiddenX" Value="0" runat="server" />
            <asp:HiddenField ID="hiddenY" Value="0" runat="server" />
            <asp:HiddenField ID="hiddenScale" Value="0" runat="server" />
            <asp:HiddenField ID="hiddenAngle" Value="0" runat="server" />
            <textarea id="commentTextArea" runat="server" Visible='<%# canAddComment() %>' name="message" rows="5" cols="70" ></textarea> <br/>
            <asp:Button ID="btnAddComment" runat="server" Visible='<%# canAddComment() %>' Text="Add Comment" style="margin:20px" OnClick="btnAddComment_Click" />
            <asp:Button ID="btnDeletePhoto" runat="server" Visible='<%# canDeletePhoto() && canAddComment() %>' Text="Delete Photo" style="margin:20px" OnClick="btnDeletePhoto_Click" />
            <asp:Button ID="btnSave" runat="server" Visible='<%# canDeletePhoto() && canAddComment() %>' Text="Save Photo" style="margin:20px" OnClick="btnSavePhoto_Click" />
    </form>
        <div>
        <asp:XmlDataSource ID="XDSComment" runat="server" XPath="Comments/Comment" EnableCaching="false"></asp:XmlDataSource>

        <asp:Repeater ID="Repeater1" runat="server" DataSourceID="XDSComment">
            <ItemTemplate>
                    <div style="display:block; width: auto; margin:10px" DataSource='<%# XPathSelect("Comment") %>'>
                        <asp:HyperLink ID="HyperLinkUser" NavigateUrl='<%# "~/MyProfile.aspx?userId=" + XPath("@Id") %>' runat="server" style="float:left; display:block;margin:10px"><%#getUsernameById(XPath("@user").ToString())%></asp:HyperLink>
                        <asp:HyperLink ID="HyperLink1" Visible='<%# canDeleteComment(XPath("@user").ToString()) %>' NavigateUrl='<%# "~/DeleteComment.aspx?commentId=" + XPath("@Id") %>' runat="server" style="float:right; margin:10px;display:block;">Delete</asp:HyperLink>
                        <div style="background-color: #cceeff; display:block; text-align: left;width: auto; height:auto; padding: 25px"><%#XPath("@text")%></div>
                    </div>
            </ItemTemplate>
            <SeparatorTemplate>
                <br />
            </SeparatorTemplate>
        </asp:Repeater>
    </div>
  </div>

  <script src='http://code.jquery.com/jquery-1.11.0.min.js'></script>
  <script src='../js/jquery.guillotine.js'></script>
    <script src='https://github.com/douglascrockford/JSON-js/blob/master/json2.js' ></script>
  <script type='text/javascript'>
      jQuery(function () {
          var picture = $('#<%=uploadedImage.ClientID%>');//$('#uploadedImage');

          // Make sure the image is completely loaded before calling the plugin
          picture.one('load', function () {
              // Initialize plugin (with custom event)
              picture.guillotine({ eventOnChange: 'guillotinechange' });

              // Display inital data
              var data = picture.guillotine('getData');
              for (var key in data) {
                  if (key == "x") {
                      $('#' + '<%=x.ClientID%>').html(data[key]);
                          $('#' + '<%=hiddenX.ClientID%>').val(data[key]);
                      }
                      else
                          if (key == 'y') {
                              $('#' + '<%=y.ClientID%>').html(data[key]);
                              $('#' + '<%=hiddenY.ClientID%>').val(data[key]);
                          }
                          else
                              if (key == 'scale') {
                                  $('#' + '<%=scale.ClientID%>').html(data[key]);
                                  $('#' + '<%=hiddenScale.ClientID%>').val(data[key]);
                              }
                              else
                                  if (key == 'angle') {
                                      $('#' + '<%=angle.ClientID%>').html(data[key]);
                                      $('#' + '<%=hiddenAngle.ClientID%>').val(data[key]);
                                  }
                                  else {
                                      $('#' + key).html(data[key]);
                                  }
              }

              // Bind button actions
              $('#rotate_left').click(function () { picture.guillotine('rotateLeft'); });
              $('#rotate_right').click(function () { picture.guillotine('rotateRight'); });
              $('#fit').click(function () { picture.guillotine('fit'); });
              $('#zoom_in').click(function () { picture.guillotine('zoomIn'); });
              $('#zoom_out').click(function () { picture.guillotine('zoomOut'); });

              $('#' + '<%=hiddenScale.ClientID%>').value = 'ceva';
              //document.getElementById("hiddenScale").value = 'ceva2';

              // Update data on change
              picture.on('guillotinechange', function (ev, data, action) {
                  data.scale = parseFloat(data.scale.toFixed(4));

                  console.log(JSON.stringify(data));
                  for (var key in data) {
                      //console.log(key + data[key]);
                      if (key === "x") {
                          $('#' + '<%=x.ClientID%>').html(data[key]);
                          $('#' + '<%=hiddenX.ClientID%>').val(data[key]);
                      }
                      else
                          if (key == 'y') {
                              $('#' + '<%=y.ClientID%>').html(data[key]);
                              $('#' + '<%=hiddenY.ClientID%>').val(data[key]);
                          }
                          else
                              if (key == 'scale') {
                                  $('#' + '<%=scale.ClientID%>').html(data[key]);
                                  $('#' + '<%=hiddenScale.ClientID%>').val(data[key]);
                              }
                              else
                                  if (key == 'angle') {
                                      $('#' + '<%=angle.ClientID%>').html(data[key]);
                                      $('#' + '<%=hiddenAngle.ClientID%>').val(data[key]);
                                  }
                                  else {
                                      $('#' + key).html(data[key]);
                                  }
                  }
              });

          });

          // Make sure the 'load' event is triggered at least once (for cached images)
          if (picture.prop('complete')) picture.trigger('load')
      });
  </script>
    
    
</asp:Content>